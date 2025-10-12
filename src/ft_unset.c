/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 19:52:38 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 15:44:31 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env_delete_1node(t_env *env)
{
	if (env->id)
		free(env->id);
	if (env->value)
		free(env->value);
	if (env->env_line)
		free(env->env_line);
	free(env);
}

int	delete_envvar(char *env_id, t_env **env)
{
	t_env	*head;
	t_env	*to_delete;

	head = get_env(env_id, *env);
	if (!head)
		return (SUCCESS);
	if (*env == head)
		*env = head->next;
	else
	{
		to_delete = *env;
		while (to_delete->next != head)
			to_delete = to_delete->next;
		to_delete->next = head->next;
	}
	env_delete_1node(head);
	return (SUCCESS);
}

int	ft_unset(t_shell *content, t_arg *args)
{
	if (!args)
		return (SUCCESS);
	else
	{
		while (args)
		{
			if (delete_envvar(args->value, &(content->env)) != 0)
				return (FAIL);
			args = args->next;
		}
	}
	return (SUCCESS);
}
