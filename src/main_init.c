/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:36:34 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/24 19:15:56 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

volatile sig_atomic_t	g_signal = 0;

t_env	*set_default_env(void)
{
	char	*env_id;
	char	*env_value;
	t_env	*def_content;

	env_id = get_env_id(DEFAULT_ENV);
	env_value = get_env_value(DEFAULT_ENV);
	def_content = env_make(env_id, env_value, ft_strdup(DEFAULT_ENV));
	return (def_content);
}

t_env	*dup_env(char *env[])
{
	t_env	*res_env;
	t_env	*tmp;
	char	*env_id;
	char	*env_value;
	int		i;

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

int	init_exec(t_shell *content, t_token **token)
{
	content->exec = build_to_exec(*token);
	token_free(*token);
	*token = NULL;
	if (!content->exec)
		return (FAIL);
	content->ct_exec = ft_build_lstsize(content->exec);
	content->pids = malloc(sizeof(pid_t) * (content->ct_exec + 1));
	if (!content->pids)
		return (FAIL);
	content->ct_pid = 0;
	return (SUCCESS);
}

int	process_input(t_shell *content, char *line)
{
	t_token	*token;
	int		pars;

	init_ignore_signal();
	token = lexing(content, line);
	free(line);
	if (!token)
		return (SUCCESS);
	pars = parsing(&token);
	if (pars)
	{
		token_free(token);
		if (pars == FAIL_VOID)
			return (SUCCESS);
		return (FAIL);
	}
	if (init_exec(content, &token) != 0)
		return (FAIL);
	exec(content);
	free_after_process(content, token);
	return (SUCCESS);
}

/* before modified signal
int	process_input(t_shell *content, char *line)
{
	t_token	*token;
	int		pars;

	token = lexing(content, line);
	free(line);
	if (!token)
		return (SUCCESS);
	pars = parsing(&token);
	if (pars)
	{
		token_free(token);
		if (pars = FAIL_VOID);
			return (SUCCESS);
		return (FAIL);
	}
	if (init_exec(content, &token) != 0);
		return (FAIL);
	exec(content);
	free_after_process(content, token);
	return (SUCCESS);
}
*/
