/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 02:36:31 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/04 21:38:07 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	len;

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
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2);
	s3 = (char *)malloc(total_len + 1);
	if (!s3)
		return (NULL);
	ft_strcpy(s3, s1);
	ft_strlcat(s3, s2, total_len + 1);
	return (s3);
}