/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:00:59 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/23 20:32:30 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// original document name: exec_toolbox1

int	ft_env_lstsize(t_env *env)
{
	int	ct;

	ct = 0;
	while (env)
	{
		ct++;
		env = env->next;
	}
	return (ct);
}

void	set_std(t_shell *stx, int mode)
{
	if (!mode)
	{
		ctx->default_in = dup(STDIN_FILENO);
	}
}
