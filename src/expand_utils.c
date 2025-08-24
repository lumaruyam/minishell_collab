/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 18:27:11 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/24 18:31:46 by lulimaruyam      ###   ########.fr       */
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
