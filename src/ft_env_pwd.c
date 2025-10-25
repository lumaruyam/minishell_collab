/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:01:47 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/24 21:12:07 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_env(t_shell *content, t_arg *args)
{
	t_env	*env;
	env = content->env;

	if (args)
	{
		error_env(args->value);
		content->exit_code = CMD_NOT_FOUND;
		return (FAIL);
	}
	if (!env)
		return (SUCCESS);
	while (env)
	{
		if (env->env_line)
			printf("%s\n", env->env_line);
		env = env->next;
	}
	return (SUCCESS);
}

// int	ft_env(t_shell *content, t_arg *args)
// {
// 	t_env	*env;

// 	env = content->env;
// 	if (args)
// 	{
// 		error_env(args->value);
// 		content->exit_code = CMD_NOT_FOUND;
// 	}
// 	if (!env)
// 		return (SUCCESS);
// 	while (env)
// 	{
// 		if (env->value)
// 			printf("%s\n", env->env_line);
// 		env = env->next;
// 	}
// 	return (SUCCESS);
// }

int	ft_pwd(t_arg *args)
{
	char	*cwd;

	if (args && *(args->value) == '-' && ft_strcmp(args->value, "-L") != 0
		&& ft_strcmp(args->value, "-P") != 0)
	{
		error_pwd(args->value);
		return (FAIL_VOID);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd: error retrieving current directory");
		return (FAIL);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}
