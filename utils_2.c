/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:57:02 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/01 11:16:13 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dest, char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dest;
	size_t	i;

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

char	*join_input(char **splited, int words_nbr)
{
	char	*joined;
	int		total_len;
	int		i;

	total_len = 0;
	i = -1;
	while (splited[++i])
		total_len += ft_strlen(splited[i]);
	total_len += (words_nbr - 1);
	joined = (char *)malloc(total_len + 1);
	if (!joined)
		return (NULL);
	i = -1;
	while (splited[++i])
	{
		ft_strlcat(joined, splited[i], total_len + 1);
		if (splited[i + 1])
			ft_strlcat(joined, " ", total_len + 1);
	}
	return (joined);
}