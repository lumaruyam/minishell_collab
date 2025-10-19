/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_to_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:32:01 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/19 19:33:08 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_exec	*init_build(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->cmd = NULL;
	new->args = NULL;
	new->redirs = NULL;
	new->next = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	return (new);
}

int	bd_handle_pipe(t_exec *exec, t_token *token)
{
	if (token->type == PIPE)
	{
		exec->next = build_to_exec(token->next);
		return (FAIL);
	}
	return (SUCCESS);
}

int	bd_handle_cmd(t_exec *exec, t_token *token)
{
	if (token->type == CMD)
	{
		exec->cmd = ft_strdup(token->value);
		if (!exec->cmd)
			return (FAIL);
	}
	return (SUCCESS);
}

t_exec	*build_to_exec(t_token *token)
{
	t_exec	*exec;

	exec = init_build();
	if (!exec)
		return (NULL);
	while (token != NULL)
	{
		if (bd_handle_pipe(exec, token) == FAIL)
			break ;
		if (bd_handle_cmd(exec, token) == FAIL)
			return (NULL);
		bd_handle_redirs(exec, token);
		bd_handle_args(exec, token);
		token = token->next;
	}
	return (exec);
}
