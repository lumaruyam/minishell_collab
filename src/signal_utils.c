/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 21:29:27 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/19 19:38:39 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signal_child_process(void)//implemet this before exective
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

static void	sigint_heredoc(int sig)
{
	g_signal.signal_code = 128 + sig;
}

void	init_signal_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &sigint_heredoc;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	init_ignore_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTSTP, &sa, NULL);
}

void	signal_to_action(t_shell *data)
{
	if (g_signal.signal_code == 128 + SIGINT && data->child_end_with_signal)
		ft_putchar_fd('\n', STDERR_FILENO);
	else if (g_signal.signal_code == 128
		+ SIGQUIT && data->child_end_with_signal)
		ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	data->child_end_with_signal = false;
	if (g_signal.signal_code)
		data->exit_code = g_signal.signal_code;
	g_signal.signal_code = 0;
}
