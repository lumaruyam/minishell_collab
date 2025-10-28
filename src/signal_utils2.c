/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:19:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/28 16:30:35 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	sig_exit(void)
{
	if (g_signal != 0)
		return (1);
	return (0);
}

void	sigint_exec(int status)
{
	(void)status;
	g_signal = SIGINT + SIG_OFFSET ;
	write(STDERR_FILENO, "\n", 1);
}

void	sigint_handler_exit(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_DFL);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	kill(0, SIGINT);
}

void	sig_heredoc(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler_exit;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
}
