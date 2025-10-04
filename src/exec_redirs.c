
#include "../inc/minishell.h"

int	redirs_type(t_filename *file)
{
	int	fd;
	int	target_fd;
	int	flags;

	fd = -1;
	target_fd = STDOUT_FILENO;
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (file->type == INFILE || file->type == NON_HEREDOC)
	{
		target_fd = STDIN_FILENO;
		FLAGTS = O_RDONLY;
	}
	else if (file->type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(file->path, flags, 0644);
	if (fd == -1)
		return (err_open(errno, file->path), 1)//start from here 1005
}

int	err_redirs(t_exec *exec, t_shell *content)
{
	t_filename	redirs;

	redirs = exec->redirs;
	while (redirs)
	{
		if (redirs_type(redirs))//start from here 1005
	}
}
