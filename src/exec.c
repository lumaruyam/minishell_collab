/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:08:00 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/21 10:02:17 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	handle_single_redir(t_shell *content, t_exec *tmp)
{
	if (err_redirs(tmp, content))
	{
		content->exit_code = 1;
		return (content->exit_code);
	}
	unlink_all(content);
	set_std(content, 1);
	return (0);
}

static int	handle_single_builtin(t_shell *content, t_exec *tmp)
{
	if (err_redirs(tmp, content))
	{
		content->exit_code = 1;
		return (content->exit_code);
	}
	if (check_is_builtin(tmp->cmd) == 2)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	unlink_all(content);
	content->exit_code = exec_builtin(content, tmp->cmd, tmp->args);
	set_std(content, 1);
	return (content->exit_code);
}

int	exec(t_shell *content)
{
	t_exec	*tmp;

	if (content->ct_exec == 0)
		return (0);
	set_std(content, 0);
	tmp = content->exec;
	if (content->ct_exec == 1)
	{
		if (tmp->cmd == NULL && tmp->redirs != NULL)
			return (handle_single_redir(content, tmp));
		if (check_is_builtin(tmp->cmd))
			return (handle_single_builtin(content, tmp));
	}
	init_signal_exec();
	exec_parent(content);
	return (0);
}
