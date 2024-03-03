/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/03 06:50:39 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sigint = 0;

int	check_syntax(t_token *tokens)
{
	(void)tokens;
	return (1);
}

int	not_escaped(char *input, int index)
{
	int	i;
	int	backslash;

	i = 0;
	backslash = 0;
	while (i < index)
	{
		if (input[i] == '\\')
			backslash++;
		else
			backslash = 0;
		i++;
	}
	return (backslash % 2 == 0);
}

int	closed_quote(char *input)
{
	int	i;
	int	signle_q;
	int	double_q;

	i = 0;
	signle_q = 0;
	double_q = 0;
	while (input[i])
	{
		if (input[i] == '\"' && not_escaped(input, i))
			double_q++;
		if (input[i] == '\'' && not_escaped(input, i))
			signle_q++;
		i++;
	}
	return (!(double_q % 2) && !(signle_q % 2));
}

int	process_input(char *input)
{
	char	**splited_input;
	t_token	*tokens;

	if (!closed_quote(input))
		return (0);
	splited_input = ft_split(input, ' ');
	if (!splited_input)
		return (0);
	tokens = malloc(sizeof(t_token) * (count_words(input, ' ') + 1));
	if (!tokens)
		return (0);
	fill_tokens(tokens, splited_input, count_words(input, ' '));
	free(splited_input);
	int i = -1;
	while (tokens[++i].value)
		printf("<%s> %d\n", tokens[i].value, tokens[i].type);
	return (1);
}

void sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	rl_replace_line();
}

void sigquit_handler(int sig)
{
	(void)sig;
	printf("Quit\n");
	exit(131);
}

void handle_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

int read_input(char *input, char *cwd)
{
	while (1)
	{
		if (g_sigint)
		{
			g_sigint = 0;
			input = readline(cwd);
		}
		else
		{
			input = readline(cwd);
			if (input[0])
				add_history(input);
			else
				ft_strcpy(input, history_get(history_length)->line);
		}
		if (!process_input(input))
			printf("failed\n");
		free(input);
	}
	return (1);
}

int main()
{
	char *cwd;
	char *input;

	cwd = malloc(BUFFER_SIZE);
	input = NULL;
	if (!cwd)
		perror("error");
	if (getcwd(cwd, BUFFER_SIZE))
		cwd = ft_strjoin(cwd, " » ");
	else
		(perror("error"), free(cwd));
	handle_signals();
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(input, cwd))
		return (1);
	(free(input), free(cwd), printf(" exit\n"), exit(0));
}
