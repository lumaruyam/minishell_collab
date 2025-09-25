/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 19:59:14 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/25 19:14:15 by lulmaruy         ###   ########.fr       */
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

static int	chk_overflow(long res, int sign, char digit)
{
	long	limit;
	long	digit_value;

	digit_value = digit - '0';
	if (sign == 1)
	{
		limit = LONG_MAX / 10;
		if (res > limit || (res == limit && digit_value > LONG_MAX % 10))
			return (1);
	}
	else
	{
		limit = -(LONG_MIN / 10);
		if (res > limit || (res == limit && digit_value > -(LONG_MIN % 10)))
			return (1);
	}
	return (0);
}

static int	ft_atol_overflow(const char *str, long *result)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (chk_overflow(res, sign, *str) == 1)
			return (1);
		res = res * 10 + (*str - '0');
		str++;
	}
	*result = res * sign;
	return (0);
}

static int	too_many(t_shell *content)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	content->exit_code = 1;
	return (1);
}

int	ft_exit(t_shell *content, t_arg *args)
{
	long	exit_code;

	exit_code = content->exit_code;
	if (args)
	{
		if (chk_exitcode(args->value) || ft_atol_overflow(args->value,
				&exit_code))
		{
			error_exit(args->value);
			exit_code = 2;
		}
		else if (args->next)
			return (too_many(content));
		else
			exit_code = (unsigned char)(exit_code % 256);
	}
	else
	{
		if (g_signal.signal_code > 0)
			exit_code =  128 + (g_signal.signal_code - SIG_OFFSET);//signal
	}
	set_std(content, 1);
	free_shell(content);
	exit(exit_code);
}
