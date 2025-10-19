/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:42:20 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/19 17:02:12 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	init_sigint(int status)
{
	(void)status;
	if (g_signal.signal_code != 1)
	{
	g_signal.signal_code = SIGINT + SIG_OFFSET;
	write(STDIN_FILENO, "\n", 1);
	}
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	signal(SIGINT, init_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_heredoc(int status)
{
	(void)status;
	g_signal.end_heredoc = 1;
	g_signal.signal_code = SIG_OFFSET + SIGINT;
}

void	sigint_exec(int status)
{
	(void)status;
	g_signal.signal_code = SIGINT + SIG_OFFSET ;
	write(STDERR_FILENO, "\n", 1);
}
