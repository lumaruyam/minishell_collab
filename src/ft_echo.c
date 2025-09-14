/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 20:57:43 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/14 21:16:32 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

static int	chk_n_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(t_arg *args)
{
	int	n_flag;

	n_flag = 0;
	while (args && args->value && chk_n_option(args->value))
	{
		n_flag = 1;
		args = args->next;
	}
	while (args)
	{
		ft_printf("%s", args->value);
		if (args->next)
			ft_printf(" ");
		args = args->next;
	}
	if (!n_flag)
		ft_printf("\n");
	return (SUCCESS);
}
