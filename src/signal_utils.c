/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:29:27 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/25 15:06:30 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_child_process(void)//implemet this before exective
{
	rl_event_hook = sig_exit;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

static void	sigint_heredoc(int sig)
{
	g_signal = 128 + sig;
	write(STDERR_FILENO, "\n", 1);
	rl_done = 1;
}

// static void	sigint_heredoc(int sig)
// {
// 	g_signal = 128 + sig;
// 	write(STDERR_FILENO, "\n", 1);
// 	rl_done = 1;
// 	// close(STDIN_FILENO);
// 	printf("DEBUG sigint_heredoc: g_signal set to %d, rl_done set\n", g_signal);
// }

// static void	sigint_heredoc(int sig)
// {
// 	g_signal = 128 + sig;
// 	rl_done = 1;
// }

void	init_signal_heredoc(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	rl_event_hook = sig_exit;
	sigemptyset(&sa_int.sa_mask);
	sigemptyset(&sa_quit.sa_mask);
	sa_int.sa_flags = SA_RESTART;  // 重要なフラグ
	sa_quit.sa_flags = 0;
	sa_int.sa_handler = &sigint_heredoc;
	sa_quit.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
}

// void	init_signal_heredoc(void)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;

// 	sigemptyset(&sa_int.sa_mask);
// 	sigemptyset(&sa_quit.sa_mask);
// 	sa_int.sa_flags = 0;
// 	sa_quit.sa_flags = 0;
// 	sa_int.sa_handler = &sigint_heredoc;
// 	sa_quit.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sa_int, NULL);
// 	sigaction(SIGQUIT, &sa_quit, NULL);
// }

// void	init_signal_heredoc(void)
// {
// 	struct sigaction	sa;

// 	// rl_event_hook = sig_exit;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_RESTART;
// 	sa.sa_handler = &sigint_heredoc;
// 	sigaction(SIGINT, &sa, NULL);
// 	sa.sa_handler = SIG_IGN;
// 	sigaction(SIGQUIT, &sa, NULL);
// 	sigaction(SIGTSTP, &sa, NULL);
// }

void	init_ignore_signal(void)
{
	struct sigaction	sa;

	// rl_event_hook = sig_exit;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	signal_to_action(t_shell *data)
{
	if (g_signal == 128 + SIGINT && data->child_end_with_signal)
		ft_putchar_fd('\n', STDERR_FILENO);
	else if (g_signal == 128
		+ SIGQUIT && data->child_end_with_signal)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	data->child_end_with_signal = false;
	if (g_signal)
		data->exit_code = g_signal;
	g_signal = 0;
}
