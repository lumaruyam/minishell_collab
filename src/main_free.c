/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 17:27:51 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/17 17:53:02 by lulimaruyam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_empty_line(char *line)
{
	if (line[0] == '\0')
		return (1);
	return (0);
}

void	free_after_process(t_shell *content, t_token *token)
{
	if (token)
		token_free(token);
	if (content)
	{
		if (content->exec)
		{
			build_free_all(content->exec);
			content->exec = NULL;
		}
		if (content->pids)
		{
			free(content->pids);
			content->pids = NULL;
		}
	}
}

void	free_shell(t_shell *content)
{
	if (content)
	{
		if (context->exec)
			build_free_all(content->exec);
		if (content->env)
			env_free(content->env);
		if (content->pids)
			free(content->pids);
		free(content);
	}
}
