/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:23:17 by yboutsli          #+#    #+#             */
/*   Updated: 2024/04/06 07:04:37 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_perror(char *str)
{
	write(2, "minishell: ", 11);
	perror(str);
	return (1);
}

int	last_bs(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
		i++;
	if (i >= 1 && str[i - 1] == '/')
		return (0);
	return (1);
}
