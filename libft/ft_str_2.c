/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:47:50 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/04 00:39:40 by obouchta         ###   ########.fr       */
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

char	*ft_substr(char const *s, int start, int len, t_free **ptrs)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (!len)
		return (NULL);
	subs = ft_malloc(ptrs, len + 1);
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
	dest = ft_malloc(ptrs, srclen + 1);
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

char	*ft_substr_2(char const *s, int start, int len)
{
	int		i;
	char	*subs;

	if (!s)
		return (NULL);
	if (!len)
		return (NULL);
	subs = malloc(len + 1);
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

int	ft_lstsize(t_cmd *lst)
{
	int	count;

	count = 0;
	if (lst == NULL)
		return (0);
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}


char	*ft_strjoin_2(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*p;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	p = (char *)malloc (sizeof(char) * (len_s1 + len_s2 + 1));
	if (!p)
		return (NULL);
	while (i < len_s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (j < len_s2 && s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[j + i] = '\0';
	return (p);
}

int	is_ambig(char *value)
{
	int	i;

	if (!value || !value[0])
		return (1);
	i = 0;
	while (value[i] && is_whitespace(value[i]))
		i++;
	if (!value[i])
		return (1);
	while (value[i])
	{
		if (is_whitespace(value[i]))
			break ;
		i++;
	}
	while (value[i] && is_whitespace(value[i]))
		i++;
	if (value[i])
		return (1);
	return (0);
}