/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 19:21:40 by obouchta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/16 03:26:36 by obouchta         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 00:27:51 by yboutsli         ###   ########.fr       */
>>>>>>> Othmane
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (0);
	else 
		return (1);
}

int	is_whitespace(char c)
{
	int		i;
	char	*set;
	
	i = 0;
	set = " \t\n\v\f\r";
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
<<<<<<< HEAD
}
=======
}
>>>>>>> Othmane
