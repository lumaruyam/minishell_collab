/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 20:46:11 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/25 19:49:04 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_filename	*bd_make_filenames(char *pathname, t_tokentype type)
{
	t_filename	*filename;
	char		*dup_path;

	filename = malloc(sizeof(t_filename));
	if (!filename)
		return (NULL);
	dup_path = ft_strdup(pathname);
	if (!dup_path)
		return (free(filename), NULL);
	filename->path = dup_path;
	filename->type = type;
	filename->next = NULL;
	return (filename);
}

int	filename_add_back(t_filename **head, t_filename *new)
{
	t_filename	*cur;

	if (!new)
		return (FAIL);
	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
	return (SUCCESS);
}

int	bd_handle_redirs(t_exec *exec, t_token *token)
{
	t_filename	*tmp;

	if (token->next && token->next->value != NULL && (token->type == APPEND
			|| token->type == NON_HEREDOC || token->type == INFILE
			|| token->type == OUTFILE))
	{
		tmp = bd_make_filenames(token->next->value, token->type);
		if (!tmp)
			return (FAIL_BUILD);
		filename_add_back(&(exec->redirs), tmp);
		return (FAIL);
	}
	return (SUCCESS);
}

void	filename_free(t_filename *filename)
{
	t_filename	*tmp;

	while (filename != NULL)
	{
		tmp = filename;
		if (filename->path)
			free(filename->path);
		filename = filename->next;
		free(tmp);
	}
}
