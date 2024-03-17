/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 14:43:11 by yboutsli          #+#    #+#             */
/*   Updated: 2024/03/07 19:22:44 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	t_list		*list_env;
// 	t_list		*list_set;
// 	char		**tab;
// 	int		status;
// 	// atexit(lls);
// 	(void)argc;
// 	(void)argv;
// 	status = 0;
// 	list_set = NULL;
// 	list_env = env_lst(envp);
// 	if (!list_env)
// 		env_init(&list_env);
// 	input = readline("");
// 	while (input)
// 	{
// 		tab = ft_split(input, ' ');
// 		// print_tab(tab);
// 		if (!set_valid(input))
// 			status = add_set(&list_set, input);
// 		if (!ft_strcmp(tab[0], "cd"))
// 			status = cd(tab[1], &list_env);
// 		else if(!ft_strcmp(tab[0], "pwd"))
// 			status = pwd();
// 		else if(!ft_strcmp(tab[0], "echo"))
// 			status = echo(tab[1], 1, list_env, list_set);
// 		else if (!ft_strcmp(tab[0], "env"))
// 			status = env(list_env);
// 		// status = echo(input, 1, list_env, list_set);
// 		// else
// 		// {
// 		// status = cd(input, &list_env);
// 		// }
// 		free(input);
// 		free_tab(tab);
// 		input = readline("");
// 	}
// 	free(input);
// 	ft_lstfree(&list_env);
// 	ft_lstfree(&list_set);
// 	return (0);
// }
