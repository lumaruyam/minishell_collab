/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:33:25 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/07/08 21:29:36 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	read_loop(t_shell *content)
{
	char	*line;

	(void)content;
	line = NULL;
	while (1)
	{
		init_signals();
		line = readline("minishell> ");
		if (!line)
			free_all(); // add free_all later

	}
}

int	main(int ac, char *av, char **env)
{
	t_shell	*content;

	content = NULL;
	(void)ac;
	(void)av;
	content = init_shell(env);
	if (!content)
		return (EXIT_FAILURE);
	read_loop(content);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	return (EXIT_SUCCESS);
}
