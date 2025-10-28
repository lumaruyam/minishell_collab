/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:28:55 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/28 18:39:58 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int	sig_exit(void)
// {
// 	return (EXIT_SUCCESS);
// }

void	sig_stop(void)
{
	struct sigaction	stop_sa;

	stop_sa.sa_handler = SIG_IGN;
	sigemptyset(&stop_sa.sa_mask);
	sigaddset(&stop_sa.sa_mask, SIGINT);
	stop_sa.sa_flags = 0;
	sigaction(SIGINT, &stop_sa, NULL);
}

static void	handle_signal_exec(int sig)
{
	g_signal = 128 + sig;
}

void	init_signal_exec(void)
{
	struct sigaction	sa;

	// rl_event_hook = sig_exit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handle_signal_exec;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGTSTP, &sa, NULL);
}

static void	sigint_interactive_mode(int sig)
{
	if (tcgetpgrp(STDIN_FILENO) == getpgrp())
	{
		g_signal = 128 + sig;
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal_interactive_mode(void)
{
	struct sigaction	sa;

	// rl_event_hook = sig_exit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sigint_interactive_mode;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}
