
#include "../inc/minishell.h"

void	child_process(t_shell *content, int (*fd)[2], int i, t_exec *tmp)
{
	int	exit_code;

	exit_code = 0;
	signal_child_process();//added to implement signal
	setup_redir(content, fd, i);//create this function
	if (handle_redir_and_builtins(content, tmp, &exit_code))//do we need?
		exit(exit_code);
	exit_code = ft_execution(content, tmp);//create this function
	free_shell(content);
	if (exit_code == 127)
		exit(127);
	else if (exit_code == 126)
		exit(126);
	else if (exit_code != 0)
		exit(1);
	exit(0);
}

int	exec_parent(t_shell *content)
{
	t_exec	*tmp;
	int		fd[MAX_FDS][2];
	pid_t	pid;

	tmp = content->exec;
	if (open_pipes(content->exec_count - 1, fd) == -1)
		return (err_pipe(errno, content));
	while (tmp)
	{
		signal(SIGINT, sigint_exec);
		pid = fork();
		if (pid == -1)
			return (err_fork(errno, content, fd));//create this func
		else if (pid == 0)
			child_process(content, fd, content->ct_pid, tmp);//create this
		content->pids[content->ct_pid] = pid;
		content->ct_pid++;
		tmp = tmp->next;
	}
	close_all(content->ct_exec - 1, fd);
	set_std(content, 1);
	wait_children(content->ct_pid, content);//added for signal
	signal_to_action(content);
	return (0);
}
