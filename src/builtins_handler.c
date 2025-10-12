/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:41:26 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 15:44:42 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	chk_is_builtin(char *input_cmd)
{
	if (!input_cmd)
		return (0);
	else if (ft_strcmp(input_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(input_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(input_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(input_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(inpput_cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(input_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(input_cmd, "exit") == 0)
		return (2);
	else
		return (0);
}

int	exec_builtin(t_shell *content, char *input_cmd, t_arg *args)
{
	if (ft_strcmp(input_cmd, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(input_cmd, "cd") == 0)
		return (ft_cd(content, args));
	else if (ft_strcmp(input_cmd, "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(input_cmd, "export") == 0)
		return (ft_export(content, args));
	else if (ft_strcmp(input_cmd, "unset") == 0)
		return (ft_unset(content, args));
	else if (ft_strcmp(input_cmd, "env") == 0)
		return (ft_env(content, args));
	else if (ft_strcmp(input_cmd, "exit") == 0)
		return (ft_exit(content, args));
	else
		return (0);
}
