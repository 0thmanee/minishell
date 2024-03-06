/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:41:08 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/06 03:46:36 by obouchta         ###   ########.fr       */
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
int 	ft_strcmp(const char *s1, const char *s2);
int	    valid_quotes(char *input);
int	    ft_new_len(char *input);
char	*add_spaces(char *input);
t_token	*ft_lstnew(char *value, int type, char **args);
void	ft_lstadd_back(t_token **lst, t_token *new);

#endif