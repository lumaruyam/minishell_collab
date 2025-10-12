/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:52:31 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 21:32:18 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	error_cd(int err_n, char *pathname)
{
	char	*err_msg;

	err_msg = strerror(err_n);
	if (pathname && ft_strcmp(pathname, "HOME") == 0)
	{
		ft_putstr_fd(PROMPT_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(" not set\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(PROMPT_NAME, STDERR_FILENO);
		ft_putstr_fd(": cd: ", STDERR_FILENO);
		ft_putstr_fd(pathname, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

void	error_export(char *input_line)
{
	ft_putstr_fd(PROMPT_NAME, STDERR_FILENO);
	ft_putstr_fd(": export ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(" : Not a valid identifier\n", STDERR_FILENO);
}

void	error_pwd(char *option)
{
	ft_putstr_fd(PROMPT_NAME, STDERR_FILENO);
	ft_putstr_fd(": pwd: ", STDERR_FILENO);
	ft_putstr_fd(option, STDERR_FILENO);
	ft_putstr_fd(": Invalid option\n", STDERR_FILENO);
}

void	error_env(char *input_line)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}

void	error_exit(char *input_line)
{
	ft_putstr_fd(PROMPT_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(input_line, STDERR_FILENO);
	ft_putstr_fd(": Numeric argument required\n", STDERR_FILENO);
}
