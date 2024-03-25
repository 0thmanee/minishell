/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 08:42:35 by obouchta          #+#    #+#             */
/*   Updated: 2024/03/25 06:03:48 by obouchta         ###   ########.fr       */
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

void print_it_2(t_cmd *cmds)
{
	t_cmd	*curr;
	int		i;
	curr = cmds;
	while (curr)
	{
		printf("\nvalue: (%s)\n-----------\n", curr->cmd);
		if (curr->args)
		{
			i = 0;
			printf("args :\n");
			while (curr->args[i])
			{
				printf("{ %s }\n", curr->args[i]);
				i++;
			}
		}
		printf("-----------\n");
		if (curr->infiles)
		{
			i = 0;
			printf("infiles :\n\n");
			while (curr->infiles[i].fd != -42)
			{
				printf("type: %s\n", curr->infiles[i].type == 0 ? "infile" : "here doc");
				curr->infiles[i].type == 0 ? printf("fd:[ %d ]\n", curr->infiles[i].fd) : printf("");
				if (curr->infiles[i].type == 1)
					printf("Delimiter: [ %s ]\n", curr->infiles[i].delimiter);
				printf("\n");
				i++;
			}
		}
		if (curr->outfiles)
		{
			i = 0;
			printf("outfiles :\n\n");
			while (curr->outfiles[i].fd != -42)
			{
				printf("type: %s\n", curr->outfiles[i].type == 2 ? "outfile" : "Append");
				printf("fd:[ %d ]\n", curr->outfiles[i].fd);
				printf("\n");
				i++;
			}
		}
		printf("=======================\n");
		curr = curr->next;
	}
}

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
			if (regonize_type(*input, i) != EXPRESSION && regonize_type(*input, i) != PIPE)
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

int	process_input(char *input, t_list **list_env, t_free **ptrs)
{
	t_token *tokens;
	t_cmd	*cmd;
	int		here_doc;
	int		s_error;

	(tokens = NULL, cmd = NULL, here_doc = 0, s_error = 1);
	if (!valid_quotes(input))
		return (2);
	add_spaces(&input, ptrs);
	trim_input(&input, ptrs);
	if (!input)
		return (1);
	if (!tokenize_input(&input, &tokens, ptrs))
		return (0);
	if (syntax_error(tokens, &here_doc))
	{
		if (here_doc)
			open_heredoc(tokens, here_doc, &s_error);
		if (!s_error)
			return (3);
		return (2);
	}
	join_args(&tokens, ptrs);
	specify_vars(&tokens, ptrs);
	if (!remove_quotes(&tokens, ptrs))
		return (0);
	expanding(&tokens, *list_env, ptrs);
	if (!final_command(&tokens, &cmd, ptrs))
		return (0);
	// print_it_2(cmd);
	ft_execution(&cmd, list_env, ptrs);
	ft_free_all(ptrs);
	return (1);
}

int read_input(t_list **list_env)
{
	t_list *list_set;
	char 	*input;
	t_free	*ptrs;

	(list_set = NULL, ptrs = NULL);
	using_history();
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	rl_catch_signals = 0;
	while (1)
	{
		input = readline("\033[1;32mMinishell $> \033[0m");
		if (!input)
			(printf("exit\n"), exit(0));
		if (!input[0])
		{
			free(input);
			continue ;
		}
		if (input[0])
			add_history(input);
		else if (history_length > 0)
				ft_strcpy(input, history_get(history_length)->line);
		if (process_input(input, list_env, &ptrs) == 2)
			(ft_free_all(&ptrs), printf("minishell: syntax error\n"));
	}
	return (1);
}

// void leaks()
// {
//     fclose(gfp);
//     system("leaks minishell");
//     usleep(1000 * 100 *10000);
// }
// void f(){system("leaks minishell");}

int main(int ac, char **av, char **envp)
{
	t_list		*list_env;
	if (ac != 1)
		return (printf("minishell: too many arguments\n"), 1);
	(void)av;
	list_env = env_lst(envp);
	if (!list_env)
		env_init(&list_env);
	if (!isatty(STDIN_FILENO))
		exit(1);
	if (!read_input(&list_env))
		return (1);
}
