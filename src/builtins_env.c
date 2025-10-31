/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:59:02 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/31 13:03:51 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	chk_envid_valid(char *env_id)
{
	int	i;

	i = 0;
	if (env_id[i] == '\0')
		return (0);
	if (ft_isalpha(env_id[i]) == 0 && env_id[i] != '_')
		return (0);
	i++;
	while (env_id[i])
	{
		if (ft_isalnum(env_id[i]) == 0 && env_id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	update_envvar(t_env *update_env, char *env_line)
{
	char	*env_value;

	env_value = get_env_value(env_line);
	if (!env_value)
	{
		free(env_value);
		return ;
	}
	if (update_env->value)
		free(update_env->value);
	if (update_env->env_line)
		free(update_env->env_line);
	update_env->value = env_value;
	update_env->env_line = env_line;
}

static int	make_add_env(char *env_id, char *input_line,
			char *dup_inputline, t_env **env_head)
{
	char	*env_value;
	t_env	*env;

	env_value = get_env_value(input_line);
	env = env_make(env_id, env_value, dup_inputline);
	if (!env)
	{
		free(input_line);
		if (env_value)
			free(env_value);
		free(env_id);
		return (FAIL);
	}
	env_add_back(env_head, env);
	return (SUCCESS);
}

static int	chk_dup_envvar(char *input_line, char **env_id, char **dup_input)
{
	*env_id = get_env_id(input_line);
	if (!*env_id || !chk_envid_valid(*env_id))
	{
		free(*env_id);
		error_export(input_line);
		return (FAIL);
	}
	*dup_input = ft_strdup(input_line);
	if (!dup_input)
		return (free(*env_id), FAIL);
	return (SUCCESS);
}

int	add_envvar(char *input_line, t_env **env_head)
{
	char	*env_id;
	char	*dup_inputline;
	t_env	*env;

	if (chk_dup_envvar(input_line, &env_id, &dup_inputline) == FAIL)
		return (FAIL);
	env = get_env(env_id, *env_head);
	if (!env)
	{
		if (make_add_env(env_id, input_line, dup_inputline, env_head) == FAIL)
			return (FAIL);
	}
	else
	{
		free(env_id);
		update_envvar(env, dup_inputline);
	}
	return (SUCCESS);
}

// 26 lines removed 1029
// int	add_envvar(char *input_line, t_env **env_head)
// {
// 	char	*env_id;
// 	char	*dup_inputline;
// 	t_env	*env;

// 	env_id = get_env_id(input_line);
// 	if (!env_id || !chk_envid_valid(env_id))
// 	{
// 		free(env_id);
// 		error_export(input_line);
// 		return (FAIL);
// 	}
// 	dup_inputline = ft_strdup(input_line);
// 	if (!dup_inputline)
// 		return (free(env_id), FAIL);
// 	env = get_env(env_id, *env_head);
// 	if (!env)
// 	{
// 		if (make_add_env(env_id, input_line, dup_inputline, env_head) == FAIL)
// 			return (FAIL);
// 	}
// 	else
// 	{
// 		free(env_id);
// 		update_envvar(env, dup_inputline);
// 	}
// 	return (SUCCESS);
// }
// int	add_envvar(char *input_line, t_env **env_head)
// {
// 	char	*env_id;
// 	char	*dup_inputline;
// 	t_env	*env;

// 	env_id = get_env_id(input_line);
// 	env = get_env(env_id, *env_head);
// 	if (!env_id || !chk_envid_valid(env_id))
// 		return (free(env_id), error_export(input_line), FAIL);
// 	dup_inputline = ft_strdup(input_line);
// 	if (!dup_inputline)
// 		return(free(env_id), FAIL);
// 	if (!env)
// 	{
// 		if (make_add_env(env_id, input_line, dup_inputline, env_head) == FAIL)
// 			return (FAIL);
// 	}
// 	else
// 	{
// 		free(env_id);
// 		update_envvar(env, dup_inputline);
// 	}
// 	return (SUCCESS);
// }
