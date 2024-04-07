/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitespace_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 22:22:05 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/07 00:24:03 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	words_counts_2(char const *s)
{
	size_t	count;
	size_t	i;
	int		is_word;

	is_word = 0;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (is_whitespace(s[i]))
			is_word = 0;
		else if (!is_word)
		{
			count++;
			is_word = 1;
		}
		i++;
	}
	return (count);
}

static size_t	next_len_2(char const *s)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] && is_whitespace(s[i]))
		i++;
	while (s[i] && !is_whitespace(s[i]))
	{
		i++;
		count++;
	}
	return (count);
}

static char	*next_word_2(char **s, t_free **ptrs)
{
	size_t	i;
	char	*p;
	size_t	next_lens;

	while (**s && is_whitespace(**s))
		(*s)++;
	next_lens = next_len_2(*s);
	p = ft_malloc(ptrs, next_lens + 1);
	i = 0;
	while (i < next_lens)
	{
		p[i] = **s;
		i++;
		(*s)++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_2(char *s, t_free **ptrs)
{
	size_t	n_words;
	char	**p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	n_words = words_counts_2(s);
	p = ft_malloc(ptrs, sizeof(char *) * (n_words + 1));
	while (i < n_words)
	{
		*(p + i) = next_word_2(&s, ptrs);
		if (!p[i])
		{
			while (i > 0)
				ft_free_ptr(ptrs, p[--i]);
			ft_free_ptr(ptrs, p);
			return (NULL);
		}
		i++;
	}
	p[i] = NULL;
	return (p);
}
