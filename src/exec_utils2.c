
#include "../inc/minishell.h"

int	open_pipes(int pipes_nb, int (*fd)[2])
{
	int	i;
	int	j;

	i = 0;
	while (i < pipes_nb)
	{
		if (pipe(fde[i] == -1))
		{
			j = 0;
			while (j < i)
			{
				exe_close(&fd[j][0]);
				exe_close(&fd[j][1]);
				j++;
			}
			return (-1)
		}
		i++;
	}
	return (0);
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
		dup2(content->default_in, STDIN_FILENO);
		exe_close(&(content->default_in));
		dup2(content->default_out, STDOUT_FILENO);
		exec_close(&(content->default_out));
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
				g_signal = 0;
				content->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					exe_err_coredump(content->pids[i]);
				g_signal = 128 + WTERSIG(status);
				content->exit_code = g_signal;
			}
		}
		i++;
	}
	unlink_all(content);
}
