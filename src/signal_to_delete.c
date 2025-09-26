/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_to_delete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 17:42:20 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/26 21:11:50 by lulmaruy         ###   ########.fr       */
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
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	sig_event(void)
{
	return (EXIT_SUCCESS);
}

void	init_signals(void)
{
	rl_event_hook = sig_event;
	signal(SIGINT, init_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	signals_heredoc(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_signal.end_heredoc = 1;
	g_signal.signal_code = SIG_OFFSET + SIGINT;
}

void	sigint_exec(int status)
{
	(void)status;
	g_signal.signal_code = SIGINT + SIG_OFFSET ;
	write(STDERR_FILENO, "\n", 1);
}
