/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:07:24 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/28 18:36:46 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_open(int err_no, char *file)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n", PROMPT_NAME, file, strerror(err_no));
	dup2(tmp_fd, STDOUT_FILENO);
	exe_close(&(tmp_fd));
}

int	err_pipe(int err_no, t_shell *content)
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

void	err_execve(char *path, int err_no)
{
	int			fd_tmp;
	struct stat	stats;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err_no == ENOENT && !strchr(path, '/'))
		printf("%s: %s: command not found\n", PROMPT_NAME, path);
	else if (err_no == ENOENT)
		printf("%s: %s: No such file or directory\n", PROMPT_NAME, path);
	else if (stat(path, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode) == 1)
			printf("%s: %s: Is a directory\n", PROMPT_NAME, path);
		else if (err_no == EACCES)
			printf("%s: %s: Permission denied\n", PROMPT_NAME, path);
		else
			printf("%s: %s: %s\n", PROMPT_NAME, path, strerror(err_no));
	}
	else
		printf("%s: %s: No such file or directory\n", PROMPT_NAME, path);
	dup2(fd_tmp, STDOUT_FILENO);
	exe_close(&(fd_tmp));
}

int	err_fork(int err_no, t_shell *ctx, int fd[][2])
{
	int	pipe_nb;
	int	fork_success;

	pipe_nb = ctx->ct_pid - 1;
	fork_success = ctx->ct_pid;
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", PROMPT_NAME, strerror(err_no));
	close_all(pipe_nb, fd);
	set_std(ctx, 1);
	wait_children(fork_success, ctx);
	ctx->exit_code = 2;
	return (2);
}
