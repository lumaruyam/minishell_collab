/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:43:44 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/25 20:43:46 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_build_lstsize(t_exec *exec)
{
	int	len;

	len = 0;
	while (exec)
	{
		exec = exec->next;
		len++;
	}
	return (len);
}

void	build_free_all(t_exec *exec)
{
	t_exec	*cur;

	while (exec != NULL)
	{
		cur = exec;
		if (exec->cmd)
			free(exec->cmd);
		if (exec->args)
			arg_free(exec->args);
		if (exec->redirs)
			filename_free(exec->redirs);
		exec = exec->next;
		free(cur);
	}
}
