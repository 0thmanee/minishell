/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/06 04:52:26 by obouchta         ###   ########.fr       */
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

int	regonize_type_2(int prev_type)
{
	if (prev_type == INPUT)
		return (IN_FILE);
	if (prev_type == OUTPUT || prev_type == APPEND)
		return (OUT_FILE);
	if (prev_type == HERE_DOC)
		return (DELIMITER);
	return (CMD);
}

char	*quoted_cmd(char *input, int *i)
{
	int		j;
	int		quote;
	char	*value;

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
	return (value);
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
	return (new_token);
}

int calc_args_len(char *input, int i)
{
	int len = 0;
	int l = 0;
	char quote;

	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (input[i])
				i++;
			len++;
			continue ;
		}
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
		if (input[*i] == '\'' || input[*i] == '\"')
		{
			args[l++] = quoted_cmd(input, i);
			continue ;
		}
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

t_token	*get_cmd(char *input, int *i, int prev_type)
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
	new_token = ft_lstnew(cmd, regonize_type_2(prev_type), get_args(input, i));
	if (!new_token)
		return (NULL);
	(*i)--;
	return (new_token);
}

t_token	*get_quoted(char *input, int *i, int prev_type)
{
	char	*value;
	t_token	*new_token;
	char	**args;

	value = quoted_cmd(input, i);
	if (!value)
		return (NULL);
	args = get_args(input, i);
	new_token = ft_lstnew(value, regonize_type_2(prev_type), args);
	if (!new_token)
		return (NULL);
	return (new_token);
}

int get_last_type(t_token *tokens)
{
	t_token *curr;

	curr = tokens;
	while (curr && curr->next)
		curr = curr->next;
	if (curr)
		return (curr->type);
	return (EXPRESSION);
}

void	print_the_shit(t_token *tokens)
{
	t_token *curr = tokens;
	while (curr)
	{
		printf("value: ( %s )\n", curr->value);
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
		if (curr->args && *curr->args)
		{
			if (curr->type == CMD)
			{
				printf("args:\n");
				while (curr->args && *curr->args)
				{
					printf("{ %s }\n", *curr->args);
					curr->args++;
				}	
			}
		}
		printf("\n");
		curr = curr->next;
	}
}

t_token	*ft_split(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	i = 0;
	tokens = NULL;
	while (input[i])
	{
		if (i == 0 || input[i] == ' ')
		{
			while (input[i] && input[i] == ' ')
				i++;
			if (i == ft_strlen(input))
				break ;
			if (input[i] && (input[i] == '\'' || input[i] == '\"'))
				new_token = get_quoted(input, &i, get_last_type(tokens));
			else if (regonize_type(input, i) != EXPRESSION)
				new_token = get_token(input, &i, regonize_type(input, i));
			else
				new_token = get_cmd(input, &i, get_last_type(tokens));
			if (new_token)
				ft_lstadd_back(&tokens, new_token);
		}
		else
			i++;
	}
	print_the_shit(tokens);
	return (tokens);
}

int	syntax_error(t_token *tokens)
{
	t_token *curr;;
	int		type;

	curr = tokens;
	while (curr)
	{
		type = curr->type;
		if (type == INPUT || type == OUTPUT || type == APPEND || type == PIPE)
		{
			if (!curr->next || curr->next->type == INPUT || curr->next->type == OUTPUT
				|| curr->next->type == APPEND || curr->next->type == PIPE)
				return (1);
		}
		curr = curr->next;
	}
	return (0);
}

int	process_input(char *input)
{
	t_token *tokens;

	if (!valid_quotes(input))
		return (0);
	input = add_spaces(input);
	if (!input)
		perror("error");
	tokens = ft_split(input);
	if (!tokens)
		perror("error");
	if (syntax_error(tokens))
		return (0);
	return (1);
}

int read_input(char *input, char *cwd)
{
	while (1)
	{
		input = readline(cwd);
		if (!input[0])
			continue ;
		if (input[0])
			add_history(input);
		else if (history_length > 0)
				ft_strcpy(input, history_get(history_length)->line);
		if (!process_input(input))
			printf("minishell: syntax error\n");
		free(input);
	}
	return (1);
}

int main(int ac, char **av)
{
	char *cwd;
	char *input;

	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
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
