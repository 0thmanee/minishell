/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:58:53 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/01 18:44:19 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			if (i == 0 || s[i - 1] == c)
				count++;
			i++;
		}
	}
	return (count);
}

static size_t	calc_len(char const *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static char	*fill_subs(char const **s, char c)
{
	size_t	i;
	char	*subs;
	size_t	len;

	while (**s == c && **s)
		(*s)++;
	len = calc_len(*s, c);
	subs = (char *) malloc (sizeof (char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		subs[i] = **s;
		i++;
		(*s)++;
	}
	subs[i] = '\0';
	return (subs);
}

char	**ft_split(char const *s, char c)
{
	size_t	nbr_words;
	char	**strings;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	nbr_words = count_words(s, c);
	strings = (char **) malloc (sizeof(char *) * (nbr_words + 1));
	if (!strings)
		return (NULL);
	while (i < nbr_words)
	{
		strings[i] = fill_subs(&s, c);
		if (!strings[i])
		{
			while (i > 0)
				free(strings[--i]);
			free (strings);
			return (NULL);
		}
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
