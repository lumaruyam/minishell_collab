/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:17:08 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/19 19:35:18 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envvar_len(char *envvar)
{
	int	i;

	i = 0;
	if (envvar[i] == '$')
		i++;
	if (envvar[i] == '?' || envvar[i] == '$' || envvar[i] == '\0')
		return (2);
	while (envvar[i])
	{
		if (envvar[i] != '_' && ft_isalnum(envvar[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

char	*get_envvar_name(char *envvar)
{
	int		len;
	char	*name;

	len = ft_envvar_len(envvar);
	name = ft_substr(envvar, 0, len);
	return (name);
}

char	*get_str_before_envvar(char *full_str, char *envvar)
{
	int		head_strlen;
	char	*head_str;

	head_strlen = envvar - full_str;
	if (head_strlen == 0)
		return (ft_strdup(""));
	head_str = ft_substr(full_str, 0, head_strlen);
	return (head_str);
}

char	*get_str_after_envvar(char *envvar)
{
	int		len;
	char	*new;

	len = ft_envvar_len(envvar);
	new = ft_strdup(envvar + len);
	return (new);
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
