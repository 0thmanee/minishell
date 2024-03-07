/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 21:41:01 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/07 16:36:17 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*ft_lstnew(char *value, int type, char **args)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->args = args;
	new_node->type = type;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*curr;

	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	curr = *lst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
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

char	*ft_strdup(char *str)
{
	char	*dest;
	size_t	srclen;
	size_t	i;

	srclen = ft_strlen(str);
	dest = (char *)malloc(srclen + 1);
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

char	*ft_strtrim(char *input)
{
	int	i;
	int	start;
	int	new_len;

	i = 0;
	new_len = 0;
	while (input[i] == ' ')
		i++;
	start = i;
	while (input[i])
	{
		new_len++;
		i++;
	}
	while (input[i - 1] == ' ')
	{
		new_len--;
		i--;
	}
	return (ft_substr(input, start, new_len));
}