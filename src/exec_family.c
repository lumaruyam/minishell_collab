/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_family.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:07:36 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/30 18:31:07 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_redir_and_bltins(t_shell *ctx, t_exec *tmp, int *exit_code)
{
	if (err_redirs(tmp, ctx))
	{
		ctx->exit_code = 1;
		*exit_code = ctx->exit_code;
		return (1);
	}
	if (check_is_builtin(tmp->cmd))
	{
		*exit_code = exec_builtin(ctx, tmp->cmd, tmp->args);
		return (1);
	}
	return (0);
}

// static int	handle_redir_bltins(t_shell *ctx, t_exec *tmp, int *exit_code)
// {
// 	if (err_redirs(tmp, ctx))
// 	{
// 		// free_shell(content); handle double free 1025
// 		ctx->exit_code = 1;
// 		*exit_code = ctx->exit_code;
// 		return (1);
// 	}
// 	if (check_is_builtin(tmp->cmd))
// 	{
// 		*exit_code = exec_builtin(ctx, tmp->cmd, tmp->args);
// 		// free_shell(content); handle double free 1025
// 		return (1);
// 	}
// 	return (0);
// }

// static void	setup_redir(t_shell *content, int (*fd)[2], int i)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	if (content->ct_exec > 1)
// 	{
// 		if (i > 0)
// 		{
// 			dup2(fd[i - 1][0], STDIN_FILENO);
// 			exe_close(&fd[i - 1][0]);
// 		}
// 		if (i < content->ct_exec - 1)
// 		{
// 			dup2(fd[i - 1][1], STDOUT_FILENO);
// 			exe_close(&fd[i - 1][1]);
// 		}
// 		close_fds(content->ct_exec - 1, fd, i, false);
// 	}
// 	ft_close(content);
// }

static void	setup_redir(t_shell *content, int (*fd)[2], int i)
{
	signal(SIGQUIT, SIG_DFL);
	if (content->ct_exec > 1)
	{
		if (i > 0)
		{
			dup2(fd[i - 1][0], STDIN_FILENO);
			exe_close(&fd[i - 1][0]);
		}
		if (i < content->ct_exec - 1)
		{
			dup2(fd[i][1], STDOUT_FILENO);
			exe_close(&fd[i][1]);
		}
		close_fds(content->ct_exec - 1, fd, i, false);
	}
	ft_close(content);
}

// will change for test
// static void	setup_redir(t_shell *content, int (*fd)[2], int i)
// {
// 	signal(SIGQUIT, SIG_DFL);
// 	if (content->ct_exec > 1)
// 	{
// 	// debug removed
// 		if (i > 0)
// 		{
// 			if (dup2(fd[i - 1][0], STDIN_FILENO) == -1)
// 			{
// 				err_pipe(errno, content);
// 				exit(1);
// 			}
// 			exe_close(&fd[i - 1][1]);
// 		}
// 		if (i < content->ct_exec - 1)
// 		{
// 			if (dup2(fd[i][1], STDOUT_FILENO) == -1)
// 			{
// 				err_pipe(errno, content);
// 				exit(1);
// 			}
// 			exe_close(&fd[i][1]);
// 		}
// 		close_fds(content->ct_exec - 1, fd, i, false);
// 	}
// 	ft_close(content);
// }

void	child_process(t_shell *content, int (*fd)[2], int i, t_exec *tmp)
{
	int	exit_code;

	exit_code = 0;
	signal_child_process();
	setup_redir(content, fd, i);
	if (handle_redir_and_bltins(content, tmp, &exit_code))
	{
		close_all(content->ct_exec - 1, fd);
		ft_close(content);
		free_after_process(content, NULL);
		exit(exit_code);
	}
	exit_code = ft_execution(content, tmp);
	close_all(content->ct_exec - 1, fd);
	ft_close(content);
	free_after_process(content, NULL);
	if (exit_code == 127)
		exit(127);
	else if (exit_code == 126)
		exit(126);
	else if (exit_code != 0)
		exit(1);
	exit(0);
}

// void	child_process(t_shell *content, int (*fd)[2], int i, t_exec *tmp)
// {
// 	int	exit_code;

// 	exit_code = 0;
// 	signal_child_process();//added for signal
// 	setup_redir(content, fd, i);
// 	if (handle_redir_and_bltins(content, tmp, &exit_code))
// 		exit(exit_code);
// 	exit_code = ft_execution(content, tmp);//create this function Samira
// 	free_shell(content);
// 	if (exit_code == 127)
// 		exit(127);
// 	else if (exit_code == 126)
// 		exit(126);
// 	else if (exit_code != 0)
// 		exit(1);
// 	exit(0);
// }

static int	set_fork_process(t_shell *content, int fd[MAX_FDS][2])
{
	t_exec	*tmp;
	pid_t	pid;

	tmp = content->exec;
	while (tmp)
	{
		signal(SIGINT, sigint_exec);
		pid = fork();
		if (pid == -1)
		{
			close_all(content->ct_exec - 1, fd);
			return (err_fork(errno, content, fd));
		}
		else if (pid == 0)
			child_process(content, fd, content->ct_pid, tmp);
		content->pids[content->ct_pid] = pid;
		content->ct_pid++;
		tmp = tmp->next;
	}
	return (0);
}

int	exec_parent(t_shell *content)
{
	int		res;
	int		fd[MAX_FDS][2];

	ft_memset(fd, -1, sizeof(fd));
	if (open_pipes(content->ct_exec - 1, fd) == -1)
		return (err_pipe(errno, content));
	res = set_fork_process(content, fd);
	if (res != 0)
		return (res);
	close_all(content->ct_exec - 1, fd);
	set_std(content, 1);
	wait_children(content->ct_pid, content);
	signal_to_action(content);
	return (0);
}

//within 25lines for norminette
// int	exec_parent(t_shell *content)
// {
// 	t_exec	*tmp;
// 	int		fd[MAX_FDS][2];
// 	pid_t	pid;

// 	ft_memset(fd, -1, sizeof(fd));
// 	tmp = content->exec;
// 	if (open_pipes(content->ct_exec - 1, fd) == -1)
// 		return (err_pipe(errno, content));
// 	while (tmp)
// 	{
// 		signal(SIGINT, sigint_exec);
// 		pid = fork();
// 		if (pid == -1)
// 		{
// 			close_all(content->ct_exec - 1, fd);
// 			return (err_fork(errno, content, fd));
// 		}
// 		else if (pid == 0)
// 			child_process(content, fd, content->ct_pid, tmp);
// 		content->pids[content->ct_pid] = pid;
// 		content->ct_pid++;
// 		tmp = tmp->next;
// 	}
// 	close_all(content->ct_exec - 1, fd);
// 	set_std(content, 1);
// 	wait_children(content->ct_pid, content);
// 	signal_to_action(content);
// 	return (0);
// }

// int	exec_parent(t_shell *content)
// {
// 	t_exec	*tmp;
// 	int		fd[MAX_FDS][2];
// 	pid_t	pid;

// 	tmp = content->exec;
// 	if (open_pipes(content->ct_exec - 1, fd) == -1)
// 		return (err_pipe(errno, content));
// 	while (tmp)
// 	{int	prs_handle_cmd(t_token *token)
// {
// 	while (token != NULL)
// 	{
// 		if (token->type == STR)
// 		{
// 			token->type = CMD;
// 			while (token != NULL && token->type != PIPE)
// 			{
// 				if (token->type == STR)
// 					token->type = ARG;
// 				token = token->next;
// 			}
// 		}
// 		if (token != NULL)
// 			token = token->next;
// 	}
// 	return (SUCCESS);
// }
// 	signal(SIGINT, sigint_exec);
// 		pid = fork();
// 		if (pid == -1)
// 			return (err_fork(errno, content, fd));//create this func Samira
// 		else if (pid == 0)
// 			child_process(content, fd, content->ct_pid, tmp);//create this
// 		content->pids[content->ct_pid] = pid;
// 		content->ct_pid++;
// 		tmp = tmp->next;
// 	}
// 	close_all(content->ct_exec - 1, fd);
// 	set_std(content, 1);
// 	wait_children(content->ct_pid, content);//added for signal
// 	signal_to_action(content);
// 	return (0);
// }
