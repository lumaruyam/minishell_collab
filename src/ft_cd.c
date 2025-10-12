/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:17:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 15:44:42 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_arg_lstsize(t_arg *args)
{
	int	ct;

	ct = 0;
	while (args)
	{
		ct++;
		args = args->next;
	}
	return (ct);
}

int	update_pwd(t_shell *content, char *oldpwd_value)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*current_cwd;
	char	*pwd_path;
	char	*oldpwd_path;

	current_cwd = getcwd(NULL, 0);
	old_pwd = get_env("OLDPWD", content->env);
	pwd = get_env("PWD", content->env);
	if (pwd && current_cwd)
	{
		pwd_path = ft_strjoin("PWD=", current_cwd);
		if (!pwd_path || add_envvar(pwd_path, &content->env) != 0)
			return (free(current_cwd), FAIL);
		free(pwd_path);
	}
	if (old_pwd && oldpwd_value)
	{
		oldpwd_path = ft_strjoin("OLDPWD=", oldpwd_value);
		if (!oldpwd_path || add_envvar(oldpwd_path, &content->env) != 0)
			return (free(current_cwd), FAIL);
		free(oldpwd_path);
	}
	free(current_cwd);
	return (SUCCESSS);
}

int	ft_cd(t_shell *content, t_arg *args)
{
	int		args_nb;
	char	*cwd;
	t_env	*home;

	args_nb = ft_arg_lstsize(args);
	if (args_nb > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: error retrieving current directory");
	home = get_env("HOME", content->env);
	if ((!args_nb || !ft_strcmp(args->value, "--")) && home && home->value)
		chdir(home->value);
	else if ((!args_nb || !ft_strcmp(args->value, "--")) && (!home || \
			!home->value))
		return (error_cd(errno, "HOME"), free(cwd), 1);
	else if (chdir(args->value) < 0)
	{
		error_cd(errno, args->value);
		return (free(cwd), 1);
	}
	if (update_pwd(content, cwd))
		return (free(cwd), 1);
	return (free(cwd), SUCCESS);
}
