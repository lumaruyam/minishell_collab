/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:27:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/28 20:10:08 by lulmaruy         ###   ########.fr       */
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

int	ft_envvar_len(char *envvar)
{
	int	i;

	i = 0;
	if (envvar[i] == '$')
		i++;
	if (ft_isdigit(envvar[i] == 1 || envvar[i] == '?' || envvar[i] == '$'))
		return (2);
	while (envvar[i])
	{
		if (envvar[i] != '_' && ft_isslnum(envvar[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*get_str_before_envvar(char *full_str, char *envvar)
{
	int		head_strlen;
	char	*head_str;

	head_strlen = envvar - full_str;
	if (head_strlen == 0)
		return (ft_strdup(""));
	head_str = ft_strdup(full_str, head_strlen);
	return (head_str);
}

char	*get_str_after_envvar(char *envvar)
{
	int		len;
	char	*new;

	len = envvar_len(envvar);
	new = ft_strdup(envvar + len);
	return (new);
}

char	*get_envvar_name(char *envvar)
{
	int	len;
	char *name;

	len = envvar_len(envvar);
	name = ft_strndup(envvar, len);
	return (name);
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

char	*get_envvar_value(char *envvar, t_shell *content)
{
	char	*path;
	t_env	*env_variable;
	char	*res;

	path = get_envvar_name(envvar);
	if (path && ft_strncmp(path, "?", 1) == 0)
	{
		res = handle_qmark_exit(content);
		free(path);
		return (res);
	}
	else if (path && ft_strcmp(path, "$") == 0)
		return (free(path), handle_dollar_pid());
	env_variable = get_env(path, content->env);
	if (path)
		free(path);
	if (!env_variable || !env_variable->value)
		return (NULL);
	return (ft_strdup(env_variable->value));
}
