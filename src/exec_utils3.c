/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 20:37:56 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/21 20:41:58 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_args_lstsize(t_arg *args)
{
	t_arg	*curr;
	int		count;

	count = 0;
	curr = args;
	while (curr)
	{
		curr = curr->next;
		count++;
	}
	return (count);
}

//args[0] = cmd
//args[1] = args1
//args[2] = args2
//args[last] = NULL
void	exec_args_create(t_exec *temp, int args_nb, char *args[args_nb])
{
	t_arg	*curr;
	int		i;

	i = 0;
	args[i] = temp->cmd;
	curr = temp->args;
	i++;
	while (curr)
	{
		args[i] = curr->value;
		curr = curr->next;
		i++;
	}
	args[i] = NULL;
}

int	ft_char_count(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i++] == c)
			count++;
	}
	return (count);
}

void	ft_free_all(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	check_is_alr_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
