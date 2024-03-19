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

#include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# define BUFFER_SIZE			2048
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

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
    char    *value;
    int     vars_len;
    int     *vars;
}   t_value;

typedef struct s_token
{
    char	*value;
    t_value   *args;
    int  args_len;
    int		type;
    int  vars_len;
    int  *vars;
    struct s_token	*next;
}	t_token;

typedef struct s_file
{
    int fd;
    int type;
    char *delimiter;
}   t_file;

typedef struct s_cmd
{
    char   *cmd;
    char   **args;
    t_file *infiles;
    t_file *outfiles;
    struct s_cmd    *next;
}   t_cmd;

typedef struct s_list
{
	char			*var;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef	struct s_free
{
	void	*ptr1;
    void    *ptr2;
	struct s_free	*next;
}	t_free;

// libft
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strlen(char *s);
int	    ft_strlcat(char *dest, char *src, int dstsize);
int	    ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strdup(char *str);
char	*ft_strtrim(char *input);
t_token	*ft_lstnew_1(char *value, int type, t_value *args);
void	ft_lstadd_back_1(t_token **lst, t_token *new_node);
t_list	*ft_lstnew_2(void *content1, void *content2);
void	ft_lstadd_back_2(t_list **lst, t_list *new);
t_cmd	*ft_lstnew_3(char *cmd, char **args, t_file *infiles, t_file *outfiles);
void	ft_lstadd_back_3(t_cmd **lst, t_cmd *new_node);
t_list	*ft_lstlast(t_list *lst);
int		ft_isalpha(int c);
char	**ft_split(char const *s, char c);
int		is_whitespace(char c);
// Parsing
int     is_whitespace(char c);
void	handle_signals(int signum);
int     ft_new_len(char *input);
int     quoted(char *input, int i);
char	*add_spaces(char *input);
int     regonize_type(char *input, int i);
int     regonize_type_2(int prev_type);
int     get_last_type(t_token *tokens);
int     calc_args_len_helper(char *input, int *i, int *len);
int     calc_args_len(char *input, int i);
t_token	*get_cmd(char *input, int *i, int prev_type);
t_value *get_values(char *input, int *i, int *args_len);
int     valid_quotes(char *input);
char	*quoted_cmd(char *input, int *i);
t_token	*get_in_out(char *input, int *i, int type, t_token **tokens);
t_token	*get_pipe(char *input, int *i, int type);
int     remove_quotes(t_token **tokens);
int     join_args(t_token **tokens);
int     extract_expr(char *src, char **dest, int *i);
void	expanding(t_token **token, t_list *list_env);
int	    final_command(t_token **tokens, t_cmd **command);
void	check_for_var_helper_1(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_2(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_3(char *value, int *vars, int *i, int *j);
int	    specify_vars(t_token **tokens);
int	    tokens_len(t_token *tokens);
int	    extract_command(t_token *token, char **cmd);
int	    extract_args(t_token *token, char ***args);
int	    extract_infiles(t_token *token, t_file **infiles);
int	    extract_outfiles(t_token *token, t_file **outfiles);
 // Removable
void	print_it(t_token *tokens);
// Execution
void	ft_execution(t_token *token, t_list **env, t_list **set);
char	*get_env(t_list **head, char *env_var);
int		env_update(t_list **head, char *env_var, char *new);
t_list	*env_lst(char **envp);
void	env_init(t_list	**env);
int	    cd(char **args, t_list **env);
int		env(t_list *list_env);
int		pwd(void);
int	    echo(t_token *token, t_list *env, t_list *set);
int		set_valid(char *str);
int		add_set(t_list **set, char *input);
void    ft_execution(t_token *token, t_list **env, t_list **set);
char	**path(t_list **envp);
void	ft_free(char **tab);
char	*cmd_path(char *cmd, char **npath);
char	**execve_argv(t_token *token, char **npath);
// char	*expanding(char *str, t_list *list_env);
#endif