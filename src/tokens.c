/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:15:18 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/09/15 20:42:02 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*create_token(char *token_value, int n,t_tokentype type, t_shell *content)
{
	t_token	*new_token;
	char	*dup_token_value;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	dup_token_value = ft_strndup(token_value, n);//need to add ft_strndup
	if (!dup_token_value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->value = dup_token_value;
	new_token->type = type;
	new_token->content = content;
	new_token->next = NULL;
	return (new_token);
}

int	token_add_back(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return (FAIL);
	if (!(*head))
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
	return (SUCCESS);
}

void	token_free(t_token *head)
{
	t_token	*current;
	t_token	*tmp_next;

	current = head;
	while (current != NULL)
	{
		tmp_next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = tmp_next;
	}
}
