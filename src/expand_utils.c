/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:27:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/09/25 19:20:41 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_expand_env(t_token *token)
{
	while (token)
	{
		if (token->type == STR || token->type == DBL_QUOTE)
			prs_envvar_expand(token);
		token = token->next;
	}
	return (SUCCESS);
}

char	*handle_qmark_exit(t_shell *content)//signal used, check later
{
	int	status_code;

	if (g_signal.signal_code != 0)
	{
		status_code = g_signal.signal_code;
		g_signal.signal_code = 0;
		return (ft_itoa(status_code));
	}
	return (ft_itoa(content->exit_code));
}

char	handle_dollar_pid(void)
{
	int	pid;

	pid = getpid();
	return (ft_itoa(pid));
}

char	*chk_null_strjoin(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s2 == NULL)
		return (s1);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

t_env	*get_env(char *env_id, t_env *env)
{
	if (env_id == NULL || env == NULL)
		return (NULL);
	while (env != NULL)
	{
		if (ft_strcmp(env_id, env->id) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}
