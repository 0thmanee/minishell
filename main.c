/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/05 06:37:31 by obouchta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add spaces when finding opearators x
// split the input into tokens
// check if the tokens are valid
// execute the command
// return 1 if the command is executed successfully
// return 0 if the command is not executed successfully
// return -1 if the command is exit
// return -2 if the command is not valid
// return -3 if the command is not found

int	regonize_type(char *input, int i)
{
	if (input[i] == '<' && input[i + 1] == '<')
		return (HERE_DOC);
	if (input[i] == '<')
		return (INPUT);
	if (input[i] == '>' && input[i + 1] == '>')
		return (APPEND);
	if (input[i] == '>')
		return (OUTPUT);
	if (input[i] == '|')
		return (PIPE);
	return (EXPRESSION);
}
t_token	*get_token(char *input, int *i, int type)
{
	int		j;
	char	*value;
	t_token	*new_token;
	int		len;

	j = 0;
	len = 1;
	if (type == APPEND || type == HERE_DOC)
		len = 2;
	value = malloc(len + 1);
	if (!value)
		return (NULL);
	while (input[*i] && input[*i] != ' ')
		value[j++] = input[(*i)++];
	value[j] = '\0';
	new_token = ft_lstnew(value, type, NULL);
	if (!new_token)
		return (NULL);
	// (*i)--;
	return (new_token);
}

int calc_args_len(char *input, int i)
{
	int len = 0;
	int l = 0;

	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (regonize_type(input, i))
			break;
		while (input[i] && input[i] != ' ')
		{
			i++;
			l++;
		}
		if (l)
			len++;
		l = 0;
	}
	return (len);
}

char **get_args(char *input, int *i)
{
	int j;
	int l;
	int len;
	char **args;

	l = 0;
	len = calc_args_len(input, *i);
	if (!len)
		return (NULL);
	args = malloc((calc_args_len(input, *i) + 2) * sizeof(char *));
	if (!args)
		return (NULL);
	while (input[*i])
	{
		while (input[*i] && input[*i] == ' ')
			(*i)++;
		if (regonize_type(input, *i) != EXPRESSION)
			break;
		j = *i;
		while (input[j] && input[j] != ' ')
			j++;
		args[l] = malloc(j - (*i) + 1);
		if (!args[l])
			return NULL;
		j = 0;
		while (input[*i] && input[*i] != ' ')
			args[l][j++] = input[(*i)++];
		args[l++][j] = '\0';
	}
	args[l] = NULL;
	return (args);
}

t_token	*get_expression(char *input, int *i)
{
	int		j;
	char	*cmd;
	t_token	*new_token;

	j = *i;
	while (input[j] && input[j] != ' ')
		j++;
	cmd = malloc(j - *i + 1);
	if (!cmd)
		return (NULL);
	j = 0;
	while (input[*i] && input[*i] != ' ')
		cmd[j++] = input[(*i)++];
	cmd[j] = '\0';
	new_token = ft_lstnew(cmd, CMD, get_args(input, i));
	if (!new_token)
		return (NULL);
	(*i)--;
	return (new_token);
}

t_token	*get_quoted(char *input, int *i)
{
	int		j;
	int		quote;
	char	*value;
	t_token	*new_token;

	quote = input[*i];
	j = (*i) + 2;
	while (input[j] && input[j] != quote)
		j++;
	value = malloc(j - *i + 2);
	if (!value)
		return (NULL);
	j = 0;
	value[j++] = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		value[j++] = input[(*i)++];
	value[j++] = input[(*i)++];
	value[j] = '\0';
	new_token = ft_lstnew(value, -1, NULL);
	if (!new_token)
		return (NULL);
	return (new_token);
}

t_token	*ft_split(char *input)
{
	t_token	*tokens = NULL;
	t_token	*new_token;
	int		i;

	i = 0;
	while (input[i])
	{
		if (i == 0 || input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (input[i] && (input[i] == '\'' || input[i] == '\"'))
				new_token = get_quoted(input, &i);
			else if (regonize_type(input, i) != EXPRESSION)
				new_token = get_token(input, &i, regonize_type(input, i));
			else
				new_token = get_expression(input, &i);
			if (new_token)
				ft_lstadd_back(&tokens, new_token);
		}
		else
			i++;
	}
	t_token *curr = tokens;
	while (curr)
	{
		printf("value: %s\n", curr->value);
		printf("type: %d\n", curr->type);
		printf("args:\n");
		while (curr->args && *curr->args)
		{
			printf("{%s}\n", *curr->args);
			curr->args++;
		}
		printf("\n");
		curr = curr->next;
	}
	return (tokens);
}

int	process_input(char *input)
{
	t_token *tokens;

	if (!valid_quotes(input))
	{
		printf("minishell: syntax error\n");
		return (0);
	}
	input = add_spaces(input);
	if (!input)
		perror("error");
	printf("{%s}\n", input);
	tokens = ft_split(input);
	return (1);
}

int read_input(char *input, char *cwd)
{
	while (1)
	{
		input = readline(cwd);
		if (input[0])
			add_history(input);
		else
			ft_strcpy(input, history_get(history_length)->line);
		if (!process_input(input))
			printf("failed\n");
		free(input);
	}
	return (1);
}

int main(int ac, char **av)
{
	char *cwd;
	char *input;

	if (ac != 1)
	{
		printf("minishell: too many arguments\n");
		return (1);
	}
	(void)av;
	cwd = malloc(BUFFER_SIZE);
	input = NULL;
	if (!cwd)
		perror("error");
	if (getcwd(cwd, BUFFER_SIZE))
		cwd = ft_strjoin(cwd, " » ");
	else
		(perror("error"), free(cwd));
	// handle_signals();
	if (!isatty(STDIN_FILENO))
		exit(1);
	using_history();
	if (!read_input(input, cwd))
		return (1);
	(free(input), free(cwd), printf(" exit\n"), exit(0));
}
