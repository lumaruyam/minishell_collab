/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 19:17:08 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/22 10:52:00 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_envvar_len(char *envvar)
{
	int	i;

	if (!envvar || !*envvar)
		return (0);
	i = 0;
	if (envvar[i] == '$')
		i++;
	if (!envvar[i])
		return (i);
	if (ft_isdigit((unsigned char)envvar[i]) || envvar[i] == '?'
			 || envvar[i] == '$')
		return (i + 1);//changed from return (2)
	while (envvar[i])
	{
		if (envvar[i] != '_' && ft_isalnum((unsigned char)envvar[i]) == 0)
			break;
		i++;
	}
	return (i);
}

char	*get_envvar_name(char *envvar)
{
	int		len;
	int		start;
	char	*name;

	len = ft_envvar_len(envvar);
	start = 0;
	if (envvar && envvar[0] == '$')
		start = 1;
	if (len <= start)
		return (ft_strdup(""));
	name = ft_strndup(envvar + start, len - start);
	return (name);
}

char	*get_str_before_envvar(char *full_str, char *envvar)
{
	int		head_strlen;
	char	*head_str;

	head_strlen = envvar - full_str;
	if (head_strlen == 0)
		return (ft_strdup(""));
	head_str = ft_strndup(full_str, head_strlen);
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
	char	*val;

	path = get_envvar_name(envvar);
	if (path && path[0] == '?' && path[1] == '\0')
		return (free(path), handle_qmark_exit(content));
	if (path && path[0] == '$' && path[1] == '\0')
		return (free(path), handle_dollar_pid());
	env_variable = get_env(path, content->env);
	if (env_variable && env_variable->value)
		return (free(path), ft_strdup(env_variable->value));
	val = getenv(path);
	if (val)
		return (free(path), ft_strdup(val));
	return (free(path), ft_strdup(""));
}

// int	ft_envvar_len(char *envvar)
// {
// 	int	i;

// 	i = 0;
// 	if (envvar[i] == '$')
// 		i++;
// 	if (ft_isdigit(envvar[i] == 1 || envvar[i] == '?' || envvar[i] == '$'))
// 		return (i + 1);//changed from return (2);
// 	while (envvar[i])
// 	{
// 		if (envvar[i] != '_' && ft_isalnum(envvar[i]) == 0)
// 			break ;
// 		i++;
// 	}
// 	return (i);
// }

// char	*get_envvar_name(char *envvar)
// {
// 	int	len;
// 	char *name;

// 	len = ft_envvar_len(envvar);
// 	name = ft_strndup(envvar, len);
// 	return (name);
// }

// char	*get_str_before_envvar(char *full_str, char *envvar)
// {
// 	int		head_strlen;
// 	char	*head_str;

// 	head_strlen = envvar - full_str;
// 	if (head_strlen == 0)
// 		return (ft_strdup(""));
// 	head_str = ft_strndup(full_str, head_strlen);
// 	return (head_str);
// }

// char	*get_str_after_envvar(char *envvar)
// {
// 	int		len;
// 	char	*new;

// 	len = ft_envvar_len(envvar);
// 	new = ft_strdup(envvar + len);
// 	return (new);
// }

// char	*get_envvar_value(char *envvar, t_shell *content)
// {
// 	char	*path;
// 	t_env	*env_variable;
// 	char	*res;

// 	path = get_envvar_name(envvar);
// 	if (path && ft_strncmp(path, "?", 1) == 0)
// 	{
// 		res = handle_qmark_exit(content);
// 		free(path);
// 		return (res);
// 	}
// 	else if (path && ft_strcmp(path, "$") == 0)
// 		return (free(path), handle_dollar_pid());
// 	env_variable = get_env(path, content->env);
// 	if (path)
// 		free(path);
// 	if (!env_variable || !env_variable->value)
// 		return (NULL);
// 	return (ft_strdup(env_variable->value));
// }
