/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouchta <obouchta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 20:15:35 by obouchta          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/03/15 23:41:11 by obouchta         ###   ########.fr       */
=======
/*   Updated: 2024/03/17 06:20:02 by obouchta         ###   ########.fr       */
>>>>>>> Othmane
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_args_helper(t_token *cmd, t_value *new_args, int *i)
{
	int	j;

	j = 0;
	if (cmd->args_len)
		while (j < cmd->args_len)
		{
			new_args[*i].value = ft_strdup(cmd->args[j].value);
			if (!new_args[*i].value)
				return (0);
			(*i)++;
			j++;
		}
	return (1);
}

<<<<<<< HEAD
int	fill_curr_f_arg(char *cmd, t_arg **new_args, int *i)
=======
int	fill_curr_f_arg(char *cmd, t_value *new_args, int *i)
>>>>>>> Othmane
{
	int	j;

	j = 0;
<<<<<<< HEAD
	new_args[*i] = malloc(sizeof(t_arg));
	if (!new_args[*i])
		return (0);
	new_args[*i]->value = ft_strdup(cmd);
	if (!new_args[*i]->value)
=======
	new_args[*i].value = ft_strdup(cmd);
	if (!new_args[*i].value)
>>>>>>> Othmane
		return (0);
	(*i)++;
	return (1);
}
<<<<<<< HEAD
int	fill_args(t_token *cmd, t_token *curr, int *len, t_arg **new_args)
=======
int	fill_args(t_token *cmd, t_token *curr, int *len, t_value *new_args)
>>>>>>> Othmane
{
	int	i;

	i = 0;
	if (!fill_args_helper(cmd, new_args, &i))
		return (0);
	if (curr->type == CMD)
	{
		if (!fill_curr_f_arg(curr->value, new_args, &i))
			return (0);
	}
	if (!fill_args_helper(curr, new_args, &i))
		return (0);
	(*len) = i;
	return (1);
}

t_value	*join_args_helper(t_token *cmd, t_token *curr, int *len)
{
<<<<<<< HEAD
	t_arg	**new_args;
=======
	t_value	*new_args;
>>>>>>> Othmane
	int		args_nbr;
	
	args_nbr = cmd->args_len + curr->args_len;
	if (curr->type == CMD)
		args_nbr++;
	if (!args_nbr)
		return (NULL);
<<<<<<< HEAD
	new_args = malloc((args_nbr + 1) * sizeof(t_arg *));
=======
	new_args = malloc((args_nbr + 1) * sizeof(t_value));
>>>>>>> Othmane
	if (!new_args)
		return (NULL);
	if (!fill_args(cmd, curr, len, new_args))
		return (NULL);
	return (new_args);
}

void remove_token(t_token **head, t_token *node_to_remove)
{
	t_token *prev = *head;
	
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		free(node_to_remove);
		return;
	}
	while (prev->next != NULL && prev->next != node_to_remove)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = node_to_remove->next;
	free(node_to_remove);
}

void remove_token(t_token **head, t_token *node_to_remove)
{
	t_token *prev = *head;
	
	if (*head == NULL || node_to_remove == NULL)
		return ;
	if (*head == node_to_remove)
	{
		*head = node_to_remove->next;
		free(node_to_remove);
		return;
	}
	while (prev->next != NULL && prev->next != node_to_remove)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = node_to_remove->next;
	free(node_to_remove);
}

void	clean_after_join(t_token **curr, t_arg **tmp, t_token **tokens)
{
	t_token *to_remove;

	(free_old_args(&((*curr)->args)), free_old_args(&tmp));
	to_remove = *curr;
	(*curr) = (*curr)->next;
	if (to_remove->type == CMD)
		remove_token(tokens, to_remove);
}

int	join_args(t_token **tokens)
{
	t_token	*curr;
	t_token	*cmd;
	t_value	*tmp;

	curr = *tokens;
	while (curr)
	{
		if (curr->type == CMD)
		{
			(cmd = curr, curr = curr->next);
			while (curr && curr->type != PIPE)
			{
				tmp = cmd->args;
				cmd->args = join_args_helper(cmd, curr, &cmd->args_len);
				curr->args_len = 0;
<<<<<<< HEAD
				clean_after_join(&curr, tmp, tokens);
=======
				curr = curr->next;
>>>>>>> Othmane
			}
		}
		else
			curr = curr->next;
	}
	return (1);
}
