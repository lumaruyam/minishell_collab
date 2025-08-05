/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:36:34 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/08/05 21:42:52 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*set_default_env(void)
{
	char	*env_id;
	char	*env_value;
	t_env	*def_content;

	env_id = get_env_id(DEFAULT_ENV);
	env_value = get_env_value(DEFAULT_ENV);
	def_content = env_create(env_id, env_value, ft_strdup(DEFAULT_ENV));
	return (def_content);
}

t_env	*dup_env(char *env[])
{
	t_env	*res_env;
	t_env	*tmp;
	char	*env_id;
	char	*env_value;
	int	i;

	i = 0;
	res_env = set_default_env();
	while (env[i])
	{
		env_id = get_env_id(env[i]);
		env_value = get_env_value(env[i]);
		tmp = env_make(env_id, env_value, ft_strdup(env[i]));
		if (!tmp)
			return (NULL);
		env_add_back(&res_env, tmp);
		i++;
	}
	return (res_env);
}

t_shell	*init_shell(char *env[])
{
	t_shell	*content;

	content = malloc(sizeof(t_shell));
	if (!content)
		return (NULL);
	content->env = dup_env(env);
	if (!(content->env))
	{
		free(content);
		return (NULL);
	}
	content->std_in = STDIN_FILENO;
	content->std_out = STDOUT_FILENO;
	content->pids = NULL;
	content->exec = NULL;
	content->ct_pid = 0;
	content->ct_exec = 0;
	content->exit_code = 0;
	return (content);
}
