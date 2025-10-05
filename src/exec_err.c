
#include "../inc/minishell.h"

void	err_open(int err_no, char *file)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n" PROMPT_NAME, file, strerror(err_no));
	dup2(RMP_FD, stdout_fileno);
	exec_close(&(tmp_fd));
}

int	err_pipe(int err_no, t_shell content)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", PROMPT_NAME, strerror(err_no));
	set_std(content, 1);
	content->exit_code = 2;
	return (FAIL_VOID);
}

void	exe_err_coredump(int pid)
{
	int	fd_backup;

	fd_backup = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("[%d]: Quit (core dumped)\n", pid);
	dup2(fd_backup, STDOUT_FILENO);
	exe_close(&fd_backup);
}
