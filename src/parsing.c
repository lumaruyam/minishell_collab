/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:32:23 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/31 17:56:42 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_chk_allnodes_null(t_token *token)
{
	while (token)
	{
		if (token->value)
			return (SUCCESS);
		token = token->next;
	}
	return (FAIL);
}

int	prs_remove_node_null(t_token **head)
{
	t_token *current;
	t_token	*token;

	token = (*head);
	while (token != NULL && token->value == NULL)
	{
		current = token;
		token = token->next;
		free(current);
	}
	*head = token;
	while (token != NULL && token->next != NULL)
	{
		if (token->next->value == NULL)
		{
			current = token->next;
			token->next = token->next->next;
			free(current);
		}
		else
			token = token->next;
	}
	return (SUCCESS);
}

int	prs_handle_cmd(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == STR)
		{
			token->type = CMD;
			while (token != NULL && token->type != PIPE)
			{
				if (token->type == STR)
					token->type = ARG;
				token = token->next;
			}
		}
		if (token != NULL)
			token = token->next;
	}
	return (SUCCESS);
}

void	prs_unlink_error(t_token *token)
{
	while (token)
	{
		if (token->type == NON_HEREDOC)
			unlink(token->next->value);
		token = token->next;
	}
}

int	parsing(t_token **token)
{
	int return_code;

	return_code = 0;
	if (prs_chk_quotes(*token) != 0)
		return_code = FAIL;
	else if (prs_quotes_n_expand_env(*token) != 0)
		return_code = FAIL;
	else if (prs_remove_node_null(token) != 0)
		return_code = FAIL;
	else if (prs_chk_allnodes_null(*token) != 0)
		return_code = FAIL_VOID;
	else if (prs_handle_redir(*token) != 0)
		return_code = FAIL;
	else if (prs_handle_cmd(*token) != 0)
		return_code = FAIL;
	else if (prs_handle_heredoc(*token) != 0)
	{
		prs_unlink_error(*token);
		return_code = FAIL_VOID;
	}
	return (return_code);
}
