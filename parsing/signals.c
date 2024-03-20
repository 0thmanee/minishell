/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:27:56 by obouchta          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2024/03/16 03:28:07 by obouchta         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 00:59:57 by obouchta         ###   ########.fr       */
>>>>>>> Othmane
=======
/*   Updated: 2024/03/20 01:24:50 by obouchta         ###   ########.fr       */
>>>>>>> Othmane
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
<<<<<<< HEAD
		g_config = 1;
=======
>>>>>>> Othmane
	}
}