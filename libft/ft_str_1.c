/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:36:31 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/26 11:49:57 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *s)
{
	int	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strlcat(char *dest, char *src, int dstsize)
{
	int	len_src;
	int	len_dest;
	int	i;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	if (!src)
		return (len_dest);
	if (dstsize <= len_dest)
		return (dstsize + len_src);
	i = 0;
	while (src[i] && len_dest + i < dstsize - 1)
	{
		dest[len_dest + i] = src[i];
		i++;
	}
	dest[len_dest + i] = '\0';
	return (len_src + len_dest);
}

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2, t_free **ptrs)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*s3;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen (s2);
	s3 = ft_malloc(ptrs, len_s1 + len_s2 + 1);
	while (s1 && i < len_s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2 && j < len_s2 && s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[j + i] = '\0';
	return (s3);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
