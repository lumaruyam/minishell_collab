/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:07:44 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/29 20:27:51 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		flags = O_RDONLY;
	}
	else if (file->type == APPEND)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(file->path, flags, 0644);
	if (fd == -1)
		return (err_open(errno, file->path), 1);
	if (dup2(fd, target_fd) == -1)
	{
		err_open(errno, file->path);
		exe_close(&fd);
		return (1);
	}
	exe_close(&fd);
	return (0);
}

int	err_redirs(t_exec *exec, t_shell *content)
{
	t_filename	*redirs;

	redirs = exec->redirs;
	while (redirs)
	{
		if (redirs_type(redirs))
		{
			if (STDIN_FILENO != content->std_in)
				dup2(content->std_in, STDIN_FILENO);
			if (STDOUT_FILENO != content->std_out)
				dup2(content->std_out, STDOUT_FILENO);
			ft_close(content);
			return (1);
		}
		if (exec->fd_in == -1 || exec->fd_out == -1)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
