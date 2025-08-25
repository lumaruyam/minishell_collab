/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:27:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/25 20:58:07 by lulimaruyam      ###   ########.fr       */
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

char	*get_str_before_envvar(char *full_str, char *envvar)
{
	int		head_strlen;
	char	*head_str;

	head_strlen = envvar - full_str;
	if (head_strlen == 0)
		return (ft_strdup(""));
	front_str = ft_strdup(full_str, head_strlen);
	return (head_str);
}

char	*get_envvar_name(char *envvar)
{
	int	len;
	char *name;

	len = envvar_len(envvar);
	name = ft_strndup(envvar, len);
	return (name);
}



char	*get_envvar_value(char *envvar, t_shell content)
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
}
