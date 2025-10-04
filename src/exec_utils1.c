/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:00:59 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/04 20:55:05 by lulmaruy         ###   ########.fr       */
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

void	exe_close(int *fd)
{
	if (fd && *fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

void	ft_close(t_shell *content)
{
	if (content)
	{
		exe_close(&(content->default_in));
		exe_close(&(content->default_out));
	}
}
