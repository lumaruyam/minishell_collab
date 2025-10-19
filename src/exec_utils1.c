/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:00:59 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/19 17:02:12 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// original document name: exec_toolbox1

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
	exe_close(&(content->std_in));
	exe_close(&(content->std_out));
	}
}

void	close_fds(int pipe_nb, int (*fd)[2], int cur_cmd, bool is_final_close)
{
	int	j;

	j = 0;
	while (j < pipe_nb)
	{
		if (!is_final_close)
		{
			if (j != cur_cmd - 1)
				exe_close(&fd[j][0]);
			if (j != cur_cmd)
				exe_close(&fd[j][1]);
		}
		else
		{
			exe_close(&fd[j][0]);
			exe_close(&fd[j][1]);
		}
		j++;
	}
}

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
