/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/15 04:57:04 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add spaces when finding opearators x
// split the input into tokens x
// check if the tokens are valid x
// execute the command
// Create builtins
// handle signals
// check exit status
// check for leaks


void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		g_config = 1;
	}
}
void	print_it(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("value: (%s)\n", curr->value);
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
		printf("Args len: %d\n", curr->args_len);
		if (curr->args)
		{
			int i = 0;
			printf("args:\n");
			while (curr->args[i])
			{
				printf("{%s}\n", curr->args[i]->value);
				i++;
			}
		}
		printf("\n");
		curr = curr->next;
	}
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
			if (regonize_type(input, i) != EXPRESSION)
				new_token = get_token(input, &i, regonize_type(input, i));
			else
				new_token = get_cmd(input, &i, get_last_type(*tokens));
			if (new_token)
				ft_lstadd_back_1(tokens, new_token);
			else
				return (0);
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

int	specify_vars(t_token **tokens)
{
	t_token	*curr;

	curr = *tokens;
	while (curr)
	{
		
		curr = curr->next;
	}
	return (1);
}

int	process_input(char *input, t_list **list_env, t_list **list_set)
{
	t_token *tokens;

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
	// if (!specify_vars(&tokens))
	// 	return (0);
	if (!remove_quotes(&tokens))
		return (0);
	if (!join_args(&tokens))
		return (0);
	print_it(tokens);
	ft_execution(tokens, list_env, list_set);
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

	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
	g_config = 0;
	(void)av;
	list_env = env_lst(envp);
	if (!list_env)
		env_init(&list_env);
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(&list_env))
		return (1);
}
