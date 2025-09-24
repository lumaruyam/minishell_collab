/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:00:59 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/24 20:10:37 by lulmaruy         ###   ########.fr       */
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

void	set_std(t_shell *content, int mode)
{
	if (!mode)
	{
		content->default_in = dup(STDIN_FILENO);
		content->defailt_out = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(content->default_in, STDIN_FILEMO);
		exe_close(&(content->default_in));
		dup2(content->default_out, STDOUT_FILENO);
		exec_close(&(content->default_out));
	}
}
