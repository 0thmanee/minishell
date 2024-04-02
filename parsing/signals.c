/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 03:27:56 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/02 06:15:11 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGQUIT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			tcsetattr(STDIN_FILENO, TCSANOW, &g_signal.original_terminos);
			printf("Quit: 3\n");
			update_exit_status(g_signal.env_lst, 131);
		}
	}
	if (signum == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
		update_exit_status(g_signal.env_lst, 1);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}