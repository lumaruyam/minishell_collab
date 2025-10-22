/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:19:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/22 21:52:10 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sigint_exec(int status)
{
	(void)status;
	g_signal = SIGINT + SIG_OFFSET ;
	write(STDERR_FILENO, "\n", 1);
}
