
#include "../inc/minishell.h"

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
		if (waitpid(contents->pids[i], &(status), 0))
		{
			if (WIFEXITED(status))
			{
				g_signal = 0;
				content->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					exe_err_coredump(content->pids[i]);//define this function
				g_signal = 128 + WTERSIG(status);
				content->exit_code = g_signal;
			}
		}
		i++;
	}
	unlink_all(content);//need to define this function
}
