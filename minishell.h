/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:26:55 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/16 03:28:22 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
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

int g_config;

typedef struct s_arg
{
    char    *value;
    int  vars_len;
    int  *vars;
} t_arg;

typedef struct s_token
{
    char	*value;
    t_arg   **args;
    int  args_len;
    int		type;
    int  vars_len;
    int  *vars;
    struct s_token	*next;
}	t_token;

typedef struct s_list
{
	void			*var;
	void			*value;
	struct s_list	*next;
}	t_list;

typedef	struct s_free
{
	void	*ptr;
	struct s_free	*next;
}	t_free;

// libft
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2);
int     ft_strlen(char *s);
int     ft_strlcat(char *dest, char *src, int dstsize);
int     ft_strcmp(const char *s1, const char *s2);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strdup(char *str);
char	*ft_strtrim(char *input);
t_token	*ft_lstnew_1(char *value, int type, t_arg **args);
void	ft_lstadd_back_1(t_token **lst, t_token *new_node);
t_list	*ft_lstnew_2(void *content1, void *content2);
void	ft_lstadd_back_2(t_list **lst, t_list *new_node);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstfree(t_list **lst);
int		ft_isalpha(int c);
int	    is_whitespace(char c);

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
t_arg   **get_args(char *input, int *i, int *args_len);
t_token	*get_cmd(char *input, int *i, int prev_type);
t_arg **get_args(char *input, int *i, int *args_len);
int     valid_quotes(char *input);
char	*quoted_cmd(char *input, int *i);
t_token	*get_in_out(char *input, int *i, int type, t_token **tokens);
t_token	*get_pipe(char *input, int *i, int type);
int     remove_quotes(t_token **tokens);
int     join_args(t_token **tokens);
int     extract_expr(char *src, char **dest, int *i);
void	check_for_var_helper_1(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_2(char *value, int *vars, int *i, int *j);
void	check_for_var_helper_3(char *value, int *vars, int *i, int *j);
int	    specify_vars(t_token **tokens);

 // Removable
void	print_it(t_token *tokens);

// Execution
void	ft_execution(t_token *token, t_list **env, t_list **set);
char	*get_env(t_list **head, char *env_var);
int		env_update(t_list **head, char *env_var, char *new);
t_list	*env_lst(char **envp);
void	env_init(t_list	**env);
int		cd(char *str, t_list **env);
int		env(t_list *list_env);
int		pwd(void);
int		echo(char *str, int nl, t_list *env, t_list *set);
int		set_valid(char *str);
int		add_set(t_list **set, char *input);
#endif