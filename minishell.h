/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:55 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/1 by ybou41li         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include <sys/ioctl.h>
# include <termios.h>
# include <signal.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <termios.h>
#include <sys/ioctl.h>
# define BUFFER_SIZE			1
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

/* in the header file */
/*==== LEAKS FINDER ==*/
// #include <libc.h>

// FILE*gfp;

// static void *__malloc(size_t size, int line, const char *file)
// {
//     void *ptr = malloc(size);
//     fprintf(gfp, "dct[%p] = ['malloc', '%p', %i, '%s']\n", ptr, ptr, line, file);fflush(gfp);
//     return (ptr);
// }


// static void __free(void *ptr, int line, const char *file)
// {
//     fprintf(gfp, "dct[%p] = ['free', '%p', %i, '%s']\n", ptr, ptr, line, file);fflush(gfp);
//     free(ptr);
// }

// #define malloc(x) __malloc(x, __LINE__, __FILE__)
// #define free(x) __free(x, __LINE__, __FILE__)

typedef enum
{
	EXPRESSION,
	CMD,
	INPUT,
	IN_FILE,
	OUTPUT,
	OUT_FILE,
	HERE_DOC,
	DELIMITER,
	APPEND,
	PIPE,
	EQUAL,
	VAR,
	VALUE,
}	TokenType;

typedef struct s_value
{
	char	*value;
	int		vars_len;
	int		*vars;
}   t_value;

typedef struct s_token
{
	char	*value;
	t_value   *args;
	int  args_len;
	int		type;
	int  vars_len;
	int  *vars;
	int	delim_flag;
	int		is_var;
	struct s_token	*next;
}	t_token;

typedef struct s_file
{
	char *file;
	int fd;
	int type;
	char *delimiter;
	int	delim_flag;
	int	is_var;
}   t_file;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	t_file *infiles;
	t_file *outfiles;
	int		io_error;
	char	*file_error;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_list
{
	char			*var;
	char			*value;
	int				type;
	int				index;
	struct s_list	*next;
}	t_list;

typedef	struct s_free
{
	void	*ptr;
	struct s_free	*next;
}	t_free;

typedef struct t_signal
{
	struct	termios original_terminos;
	t_list	**env_lst;
	t_free	**ptrs;
}	s_signal;

// Global Variable to handle the state of the terminal when Entering SIGQUIT
// and to Set The Exit Status When Entering SIGINT

s_signal	g_signal;

// libft
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2, t_free **ptrs);
int		ft_strlen(char *s);
int		ft_strlcat(char *dest, char *src, int dstsize);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, int start, int len, t_free **ptrs);
char	*ft_strdup(char *str, t_free **ptrs);
t_token	*ft_lstnew_1(char *value, int type, t_value *args, t_free **ptrs);
void	ft_lstadd_back_1(t_token **lst, t_token *new_node);
t_list	*ft_lstnew_2(void *content1, void *content2, int exit, t_free **ptrs);
void	ft_lstadd_back_2(t_list **lst, t_list *new_node);
t_cmd	*ft_lstnew_3(t_free **ptrs);
void	ft_lstadd_back_3(t_cmd **lst, t_cmd *new_node);
t_list	*ft_lstlast(t_list *lst);
int		ft_isalpha(int c);
char	**ft_split(char const *s, char c, t_free **ptrs);
int		is_whitespace(char c);
void	*ft_malloc(t_free **list_aloc, size_t size);
void	ft_free_ptr(t_free **list_aloc, void *ptr);
void	ft_free_all(t_free **list_aloc);
int		ft_isdigit(int c);
int		ft_strchr(char *str, char c);
void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *str);
int		ft_lstsize(t_cmd *lst);
int		is_ambig(char *value);


// Parsing
int 	char_is_valid(char c);
int		is_whitespace(char c);
void	handle_signals(int signum);
int		ft_new_len(char *input);
int		quoted(char *input, int i);
void	add_spaces(char **input, t_free **ptrs);
void	trim_input(char **input, t_free **ptrs);
int		regonize_type(char *input, int i);
int		regonize_type_2(int prev_type);
int		get_last_type(t_token *tokens);
int		calc_args_len_helper(char *input, int *i, int *len);
int		calc_args_len(char *input, int i);
t_token	*get_cmd(char *input, int *i, int prev_type, t_free **ptrs);
t_value *get_values(char *input, int *i, int *args_len, t_free **ptrs);
int		valid_quotes(char *input);
char	*quoted_cmd(char *input, int *i, t_free **ptrs);
t_token	*get_in_out(char *input, int *i, t_token **tokens, t_free **ptrs);
t_token	*get_pipe(char *input, int *i, int type, t_free **ptrs);
int		remove_quotes(t_token **tokens, t_free **ptrs);
void	join_args(t_token **tokens, t_free **ptrs);
int		extract_expr(char *src, char **dest, int *i, t_free **ptrs);
char	*case_1(char *result, int *i, t_list *list_env, t_free **ptrs);
char	*case_2(char *result, int *i, t_free **ptrs);
char	*case_3(char *result, int *i, t_free **ptrs);
char	*case_4(char *result, int *i, t_list *list_env, t_free **ptrs);
void	expanding(t_token **tokens, t_list *list_env, t_free **ptrs);
int		final_command(t_token **tokens, t_cmd **command, t_free **ptrs);
void	check_for_var_helper_1(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_2(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_3(char *value, int *vars, int *i, int *j);
void	specify_vars(t_token **tokens, t_free **ptrs);
int		tokens_len(t_token *tokens);
void	extract_command(t_token *token, char **cmd, t_free **ptrs);
void	extract_args(t_token *token, char ***args, char **cmd, t_free **ptrs);
void	extract_infiles(t_token *token, t_file **infiles, t_free **ptrs);
void	extract_outfiles(t_token *token, t_file **outfiles, t_free **ptrs);
int		syntax_error(t_token *tokens, int *here_doc);
int		check_braces(char *value);
void	open_heredoc(t_token *tokens, int here_doc, int *s_error);

// Execution
char	*get_env(t_list **head, char *env_var);
t_list	*get_env_node(t_list **list_env, char *var);
int		var_exist(char *var, t_list *list_env);
int		env_update(t_list **head, char *env_var, char *new, t_free **ptrs);
t_list	*env_lst(char **envp, t_free **ptrs);
void	env_init(t_list	**env, t_free **ptrs);
int		cd(char **args, t_list **env, t_free **ptrs);
int		env(t_list **list_env, t_cmd *cmd, t_free **ptrs);
int		pwd(t_list **list_env);
int		set_valid(char *str);
int		add_set(t_list **set, char *input);
int		ft_execution(t_cmd **cmd, t_list **list_env, t_free **ptrs);
char	**path(t_list **envp, t_free **ptrs);
void	ft_free(char **tab, t_free **ptrs);
char	*cmd_path(char *cmd, char **npath, t_free **ptrs, int *type);
char	**execve_argv(t_cmd *cmd, t_free **ptrs);
int		export(t_cmd *cmd, t_list **list_env, t_free **ptrs);
int		echo(t_cmd *cmd);
int 	unset(t_list **list_env, char **args, t_free **ptrs);
char	**list2tab(t_list *list_env, t_free **ptrs);
int		env_size(t_list *list_env);
void	close2(int tab[2]);
int		here_doc(t_file *infile, int mode, t_list *list_env, t_free **ptrs);
int		new_execve(t_cmd *cmd, t_list **list_env, t_free **ptrs);
int		execute_2(t_cmd **cmd_list, t_list **list_env, t_free **ptrs, int *io_fd);
int 	new_fork();
int		valid(char *str);
void 	nvalid_output(char *str1, char *str2);
void	env_lc_update(t_cmd *cmd, t_list **list_env, t_free **ptrs);
int		ft_exit(t_cmd *cmd, t_list **list_env, t_free **ptrs);
int		args_size(t_cmd *cmd);
void	update_exit_status(t_list **list_env, int status, t_free **ptrs);
int		handle_io(t_cmd *cmd, t_list *list_env, t_free **ptrs, int *io_fd);
int		execute_1(t_cmd *cmd, t_list **list_env, t_free **ptrs,  int *io_fd);
#endif