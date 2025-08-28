/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:42:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/28 20:21:39 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_ct_dollars(char *input_str)
{
	int	i;
	int	ct;

	i = 0;
	ct = 0;
	while (input_str[i])
	{
		if (input_str == '$')
			ct++;
		i++;
	}
	return (ct);
}

char	*prs_expand_1envver(char *str, char *envvar_found, t_shell *content)
{
	char	*before_envvar;
	char	*envvar_value;
	char	*after_envvar;
	char	*new;

	*before_envvar = get_str_before_envvar(str, envvar_found);
	if (!before_envvar)
		return (NULL);
	envvar_value = get_envvar_value((envvar_found + 1), content);
	after_envvar = get_str_after_envvar(envvar_found);
	if (!after_envvar)
		return (free(before_envvar), free(envvar_value), NULL);
	new = chk_null_strjoin(before_envvar, envvar_value);
	if (!new)
		return (free(before_envvar), NULL);
	new = chk_null_strjoin(new, after_envvar);
	if (envvar_value)
		free(envvar_value);
	return (free(after_envvar), new);
}

int	prs_envvar_expand(t_token *token)
{
	int		n_dollar;
	char	*current;
	char	*envvar_found;
	char	*new;

	n_dollar = prs_ct_dollars(token->value);
	while (token->value != NULL)
	{
		envvar_found = ft_strchr(token->value, '$');
		if (envvar_found == NULL || n_dollar == 0)
			break ;
		if (ft_strcmp(envvar_found, "$") == 0)
			break ;
		current = token->value;
		new = prs_expand_1envvar(token->value, envvar_found, token->content);
		if (new && new[0] == '\0')
		{
			free(new);
			new = NULL;
		}
		token->value = new;
		free(current);
		n_dollar--;
	}
	return (SUCCESS);
}
