/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:27:56 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/30 21:13:20 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &original_terminos);
			printf("\n");
		}
	}
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}