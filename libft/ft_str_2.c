/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:47:50 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/21 07:28:42 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_substr(char const *s, int start, int len)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (!len)
		return (NULL);
	subs = (char *)malloc(len + 1);
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len && s[start])
	{
		subs[i] = s[start];
		start++;
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

char	*ft_strdup(char *str, t_free **ptrs)
{
	char	*dest;
	size_t	srclen;
	size_t	i;

	if (!str)
		return (NULL);
	srclen = ft_strlen(str);
	dest = ft_malloc1(ptrs, srclen + 1);
	if (!dest)
		(ft_free_all(ptrs), exit(1));
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup_1(char *str)
{
	char	*dest;
	size_t	srclen;
	size_t	i;

	if (!str)
		return (NULL);
	srclen = ft_strlen(str);
	dest = malloc(srclen + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	ft_strtrim(char **input, t_free **ptrs)
{
	int	i;
	int	start;
	int	new_len;
	char	*tmp;

	(i = 0, new_len = 0, tmp = *input);
	while ((*input)[i] == ' ')
		i++;
	if (i == ft_strlen(*input))
	{
		(*input = NULL, ft_free_ptr(ptrs, tmp));
		return ;
	}
	start = i;
	while ((*input)[i])
	{
		new_len++;
		i++;
	}
	while (--i >= 0 && (*input)[i] == ' ')
		new_len--;
	*input = ft_substr(*input, start, new_len);
	if (!(*input))
		(ft_free_ptr(ptrs, tmp), exit(1));
	ft_free_ptr(ptrs, tmp);
}
