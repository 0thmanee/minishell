/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/17 06:34:42 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_it(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("\nvalue: (%s)\n[ ", curr->value);
		for (int i = 0; i < curr->vars_len; i++)
			printf("%d ", curr->vars[i]);
		printf("]\n");
		printf("type: ");
		if (curr->type == CMD)
			printf("CMD\n");
		else if (curr->type == INPUT)
			printf("INPUT\n");
		else if (curr->type == IN_FILE)
			printf("IN_FILE\n");
		else if (curr->type == OUTPUT)
			printf("OUTPUT\n");
		else if (curr->type == OUT_FILE)
			printf("OUT_FILE\n");
		else if (curr->type == HERE_DOC)
			printf("HERE_DOC\n");
		else if (curr->type == DELIMITER)
			printf("DELIMITER\n");
		else if (curr->type == APPEND)
			printf("APPEND\n");
		else if (curr->type == PIPE)
			printf("PIPE\n");
		if (curr->args)
		{
			int i = 0;
			printf("args [%d]:\n", curr->args_len);
			while (i < curr->args_len)
			{
				printf("{%s}\n[ ", curr->args[i].value);
				if (curr->args[i].vars_len)
					for (int j = 0; j < curr->args[i].vars_len; j++)
						printf("%d ", curr->args[i].vars[j]);
				printf("]\n");
				i++;
			}
		}
		printf("=======================\n");
		curr = curr->next;
	}
}

int	tokenize_input(char *input, t_token **tokens)
{
	t_token	*new_token;
	int		i;

	i = 0;
	while (input[i])
	{
		if (i == 0 || is_whitespace(input[i]))
		{
			while (input[i] && is_whitespace(input[i]))
				i++;
			if (regonize_type(input, i) != EXPRESSION && regonize_type(input, i) != PIPE)
				new_token = get_in_out(input, &i, regonize_type(input, i), tokens);
			else if (regonize_type(input, i) == PIPE)
				new_token = get_pipe(input, &i, PIPE);
			else
				new_token = get_cmd(input, &i, CMD);
			if (new_token)
				ft_lstadd_back_1(tokens, new_token);
		}
		else
			i++;
	}
	return (1);
}

int	syntax_error(t_token *tokens)
{
	t_token *curr;
	int		type;

	curr = tokens;
	if (curr->type == PIPE)
		return (1);
	while (curr)
	{
		type = curr->type;
		if (type == INPUT || type == OUTPUT || type == APPEND || type == HERE_DOC)
		{
			if (!curr->next || curr->next->type == INPUT || curr->next->type == OUTPUT
				|| curr->next->type == APPEND || curr->next->type == PIPE)
				return (1);
		}
		if (type == PIPE && (!curr->next || curr->next->type == PIPE))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	process_input(char *input, t_list **list_env, t_list **list_set)
{
	t_token *tokens;
	(void)list_env;
	(void)list_set;
	
	tokens = NULL;
	if (!valid_quotes(input))
		return (2);
	input = add_spaces(input);
	if (!input)
		return (0);
	input = ft_strtrim(input);
	if (!input)
		return (0);
	if (!tokenize_input(input, &tokens))
		return (0);
	if (syntax_error(tokens))
		return (2);
	if (!join_args(&tokens))
		return (0);
	if (!specify_vars(&tokens))
		return (0);
	if (!remove_quotes(&tokens))
		return (0);
	print_it(tokens);
	// expanding
	if (final_command(&tokens))
		return (0);
	// ft_execution(tokens, list_env, list_set);
	return (1);
}

int read_input(t_list **list_env)
{
	t_list *list_set;
	char 	*input;

	list_set = NULL;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	rl_catch_signals = 0;
	while (1)
	{
		input = readline("\033[1;32mMinishell $> \033[0m");
		if (!input)
			(printf("exit\n"), exit(0));
		if (!input[0])
			continue ;
		if (input[0])
			add_history(input);
		else if (history_length > 0)
				ft_strcpy(input, history_get(history_length)->line);
		if (process_input(input, list_env, &list_set) == 2)
			printf("minishell: syntax error\n");
		free(input);
	}
	return (1);
}

int main(int ac, char **av, char **envp)
{
	t_list		*list_env;

	(void)envp;
	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
	(void)av;
	// list_env = env_lst(envp);
	// if (!list_env)
	// 	env_init(&list_env);
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(&list_env))
		return (1);
}
