/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:09:34 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/03 21:18:51 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_arg	*bd_args_create(char *arg_value)
{
	t_arg	*args;
	char	*dup_arg;

	args = malloc(sizeof(t_args));
	if (!args)
		return (NULL);
	dup_arg = ft_strdup(arg_value);
	if (!dup_arg)
	{
		free(args);
		return (NULL);
	}
	args->value = dup_arg;
	args->next = NULL;
	return (args);
}

int	arg_add_back(t_arg **head, t_arg *new)
{
	t_arg	*cur;

	if (new == NULL)
		return (FAIL);
	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while(cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
	return (SUCCESS);
}

int	bd_handle_args(t_exec *exec, t_token *token)
{
	t_arg	*new;

	new = NULL;
	if (token->type == ARG)
	{
		new = bd_make_args(token->value);
		if (!new)
			return(FAIL_BUILD);
		arg_add_back(&(exec->args), new);
	}
	return (SUCCESS);
}
