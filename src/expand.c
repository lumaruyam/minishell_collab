/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:42:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/24 18:46:37 by lulimaruyam      ###   ########.fr       */
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

int	prs_envvar_expand(t_token *token)
{
	int		n_dollar;
	char	*current;
	char	*envar_found;
	char	*new;

	n_dollar = prs_ct_dollars(token->value);
}
