/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:32:23 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/23 17:06:03 by lulimaruyam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(t_token **token)
{
	int return_code;

	return_code = 0;
	if (prs_chk_quotes(*token) != 0)
		return_code = FAIL;
	else if (prs_quotes_n_expand_env(*token) != 0)
		return_code = FAIL;

}
