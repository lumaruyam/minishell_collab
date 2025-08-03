/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:36:34 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/08/03 18:00:06 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_shell	*init_shell(char *env[])
{
	t_shell	*content;

	content = malloc(sizeof(t_shell));
	if (!content)
		return (NULL);
	content->env = dup_env(env);
	if (!(content->env))
	{
		free(content);
		return (NULL);
	}
	content->std_in = STDIN_FILENO; //add this in header
	content->std_out = STDOUT_FILENO;
	content->pids = NULL;
	content->exec = NULL;
	content->ct_pid = 0;
	content->ct_exec = 0;
	content->exit_code = 0;
	return (content);
}
