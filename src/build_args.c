/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 21:09:34 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 21:26:39 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_arg	*bd_make_args(char *arg_value)
{
	t_arg	*args;
	char	*dup_arg;

	args = malloc(sizeof(t_arg));
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

void	arg_free(t_arg *args)
{
	t_arg	*tmp;

	while (args != NULL)
	{
		tmp = args;
		if (args->value)
		{
			free(args->value);
			args->value = NULL;
		}
		args = args->next;
		free(tmp);
	}
}
