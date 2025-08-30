/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:41:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/08/30 15:23:26 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_handle_redir(t_token *token)
{
	if (token && token->type == PIPE)
		return (FAIL);
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == HEREDOC || token->type == APPEND)
		{
			if (token->next == NULL || token->next->type != STR)
				return (FAIL);
			token->next->type = FILENAME;
		}
		else if (token->type == PIPE && token->next == NULL)
			return (FAIL);
		token = token->next;
	}
	return (SUCCESS);
}

static char	*create_random_filename(char *str)
{
	char			*new;
	int				i;
	unsigned long	rand;

	if (!str)
		return (NULL);
}

int	prs_handle_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token != NULL && end == 0)
	{
		filename = create_random_filename(token->next->value);
	}
}
