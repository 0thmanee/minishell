/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:41:08 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/06 07:22:15 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE			2048
# define ANSI_COLOR_CYAN		"\x1b[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"

typedef struct s_token
{
    char	*value;
    char    **args;
    int		type;
    struct s_token	*next;
}	t_token;

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
}	TokenType;

char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2);
int	    ft_strlen(char *s);
int	    ft_strlcat(char *dest, char *src, int dstsize);
int	    ft_new_len(char *input);
char	*add_spaces(char *input);
t_token	*ft_lstnew(char *value, int type, char **args);
void	ft_lstadd_back(t_token **lst, t_token *new);
int	    regonize_type(char *input, int i);
int	    regonize_type_2(int prev_type);
int     get_last_type(t_token *tokens);
int     calc_args_len_helper(char *input, int *i, int *len);
int     calc_args_len(char *input, int i);
int	    get_args_helper(char *input, int *i, int *j, char **args);
char    **get_args(char *input, int *i);
t_token	*get_cmd(char *input, int *i, int prev_type);
int	    valid_quotes(char *input);
char	*quoted_cmd(char *input, int *i);
t_token	*get_token(char *input, int *i, int type);
t_token	*get_quoted(char *input, int *i, int prev_type);

#endif