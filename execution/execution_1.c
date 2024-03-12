/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yboutsli <yboutsli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 03:41:21 by yasser03          #+#    #+#             */
/*   Updated: 2024/03/12 17:11:17 by yboutsli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute(t_token  *token, t_list **list_env, t_list **list_set)
{
    (void)list_set;
    if (!ft_strcmp(token->value, "cd"))
        cd(token->args, list_env);
    // else if (!ft_strcmp(token->value, "echo"))
    //     echo(token->args[0], 1, *list_env, *list_set);
    // else if (!ft_strcmp(token->value, "env"))
    //     env(*list_env);
    // else if (!ft_strcmp(token->value, "pwd"))
    //     pwd();
    return (0);
}

void    ft_execution(t_token *token, t_list **env, t_list **set)
{
    (void)env;
    (void)set;
    t_token *current;

    current = token;
    while (current)
    {
        if (current->type == CMD)
        {
            execute(token, env, set);
        }
        current = current->next;
    } 
}