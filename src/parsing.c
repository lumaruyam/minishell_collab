/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:32:23 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/29 21:24:38 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

}
