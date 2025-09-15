/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 21:17:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/15 21:30:21 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

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
	if ((!args_nb || !ft_strcmp(args->value, "--")) && (!home || !home->value))
		chdir(home->value);
}
