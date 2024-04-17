/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/04/17 06:46:44 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(char **input, t_token **tokens, t_free **ptrs)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while ((*input)[i])
	{
		if (i == 0 || is_whitespace((*input)[i]))
		{
			while ((*input)[i] && is_whitespace((*input)[i]))
				i++;
			if (regonize_type(*input, i) != EXPRESSION
				&& regonize_type(*input, i) != PIPE)
				new_token = get_in_out(*input, &i, tokens, ptrs);
			else if (regonize_type(*input, i) == PIPE)
				new_token = get_pipe(*input, &i, PIPE, ptrs);
			else
				new_token = get_cmd(*input, &i, CMD, ptrs);
			if (new_token)
				ft_lstadd_back_1(tokens, new_token);
		}
		else
			i++;
	}
	return ((ft_free_ptr(ptrs, *input)), 1);
}

void	init_data(t_token **tokens, t_cmd **cmd)
{
	*tokens = NULL;
	*cmd = NULL;
}

int	process_input(char *input, t_list **list_env, t_free **ptrs)
{
	t_token	*tokens;
	t_cmd	*cmd;

	init_data(&tokens, &cmd);
	if (!valid_quotes(input))
		return (ft_putstr_fd("minishell: syntax error\n", 2), 2);
	(add_spaces(&input, ptrs), trim_input(&input, ptrs));
	if (!input || !tokenize_input(&input, &tokens, ptrs))
		return (0);
	if (check_syntax(tokens))
		return (1);
	specify_vars(&tokens, ptrs);
	expanding(&tokens, *list_env, ptrs);
	remove_quotes(&tokens, ptrs);
	(join_args(&tokens, ptrs), final_command(&tokens, &cmd, ptrs));
	return (ft_execution(&cmd, list_env, ptrs), 1);
}

void	read_input(t_list **list_env, t_free **ptrs)
{
	char	*input;

	(signal(SIGINT, handle_signals), signal(SIGQUIT, handle_signals));
	rl_catch_signals = 0;
	while (1)
	{
		input = readline("Minishell $> ");
		if (!input)
			(ft_free_all(ptrs), printf("exit\n"), exit(exit_status(1, -1)));
		if (!input[0])
		{
			free(input);
			continue ;
		}
		if (input[0])
			add_history(input);
		else if (history_length)
			ft_strcpy(input, history_get(history_length)->line);
		process_input(input, list_env, ptrs);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_list			*list_env;
	t_free			*ptrs;
	struct termios	attr;

	if (ac != 1)
		return (write(2, "minishell: too many arguments\n", 30), 1);
	(void)av;
	ptrs = NULL;
	list_env = env_lst(envp, &ptrs);
	if (!list_env)
		env_init(&list_env, &ptrs);
	tcgetattr(STDIN_FILENO, &attr);
	attr.c_lflag = ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
	read_input(&list_env, &ptrs);
}
