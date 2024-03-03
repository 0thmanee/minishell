/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:41:08 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/03 02:26:08 by obouchta         ###   ########.fr       */
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
    int		type;
}	t_token;

typedef enum {
	EXPRESSION,
    SPACE,
    CLOSE_PAREN,
    OPEN_PAREN,
    INPUT,
    OUTPUT,
    HERE_DOC,
    APPEND,
    PIPE,
    OR,
    AND,
    SEMICOLON
}	TokenType;

char	**ft_split(char const *s, char c);
char	*join_input(char **splited, int words_nbr);
size_t	count_words(char const *s, char c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strjoin(char *s1, char *s2);
void	fill_tokens(t_token *tokens, char **splited, int words_nbr);

#endif