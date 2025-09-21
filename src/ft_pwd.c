/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:01:47 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/21 15:11:37 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

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
