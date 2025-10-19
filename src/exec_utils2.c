/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:07:54 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/19 17:02:12 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	open_pipes(int pipe_nb, int (*fd)[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < pipe_nb)
	{
		if (pipe(fd[i]) == -1)
		{
			j = 0;
			while (j < i)
			{
				exe_close(&fd[j][0]);
				exe_close(&fd[j][1]);
				j++;
			}
			return (-1);
		}
		i++;
	}
	return (0);
}

void	set_std(t_shell *content, int mode)
{
	if (!mode)
	{
		content->std_in = dup(STDIN_FILENO);
		content->std_out = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(content->std_in, STDIN_FILENO);
		exe_close(&(content->std_in));
		dup2(content->std_out, STDOUT_FILENO);
		exe_close(&(content->std_out));
	}
}

void	close_all(int pipe_nb, int (*fd)[2])
{
	int	i;

	i = 0;
	while (i < pipe_nb)
	{
		exe_close(&fd[i][0]);
		exe_close(&fd[i][1]);
		i++;
	}
}

void	unlink_all(t_shell *content)
{
	t_exec	*exec;
	t_filename	*redir;

	exec = content->exec;
	while (exec)
	{
		redir =exec->redirs;
		while (redir)
		{
			if (redir->type == NON_HEREDOC)
				unlink(redir->path);
			redir = redir->next;
		}
		exec = exec->next;
	}
}

void	wait_children(int ct_pid, t_shell *content)
{
	int	status;
	int	i;

	i = 0;
	while (i < ct_pid)
	{
		if (waitpid(content->pids[i], &(status), 0))
		{
			if (WIFEXITED(status))
			{
				g_signal.signal_code = 0;
				content->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					exe_err_coredump(content->pids[i]);
				g_signal.signal_code = 128 + WTERMSIG(status);
				content->exit_code = g_signal.signal_code;
			}
		}
		i++;
	}
	unlink_all(content);
}
