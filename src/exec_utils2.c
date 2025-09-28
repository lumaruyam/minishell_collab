
#include "../inc/minishell.h"

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
