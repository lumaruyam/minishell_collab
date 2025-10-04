
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
