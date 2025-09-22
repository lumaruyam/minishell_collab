/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:59:14 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/22 21:29:31 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

int	chk_exitcode(char *input_line)
{
	char	*tmp;

	tmp = input_line;
	if (!input_line || !*input_line)
		return (1);
	while (*tmp == ' ' || (*tmp >= 9 && *tmp <= 13))
		tmp++;
	if (*tmp == '\0')
		return (1);
	if ((*tmp == '+' || *tmp == '-') && *(tmp + 1))
		tmp++;
	while (*tmp)
	{
		if (!isdigit(*tmp))
			return (1);
		tmp++;
	}
	return (0);
}

static int	ft_atol_overflow(const char *str, long *res)//continue from here 0922

int	ft_exit(t_shell *content, t_arg *args)
{
	long	exit_code;

	exit_code = content->exit_code;
	if (args)
	{
		if (chk_exitcode(args->value) || ft_atol_overflow(args->value,
				&exit_code))
	}
}
