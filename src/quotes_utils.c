/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:06:59 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/10/24 18:36:39 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*prs_get_quoted_str(char *input_str, char c, t_shell *content)
{
	int				len;
	t_token			*new_token;
	t_tokentype		type;

	if (!input_str || len_quotes(input_str, c) <= 1)
		return (NULL);
	len = len_quotes(input_str, c) - 2;
	new_token = NULL;
	type = DBL_QUOTE;
	if (c == '\'')
		type = SGL_QUOTE;
	if (len > 0)
		new_token = create_token(input_str + 1, len, type, content);
	else
		new_token = create_token("\0", 1, STR, content);
	return (new_token);
}

int	rogue_len(char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == '\'' || str[len] == '\"')
			break ;
		len++;
	}
	return (len);
}

int	len_quotes(char *str, char sd_quote)
{
	int	len;

	len = 1;
	while (str[len] && str[len] != sd_quote)
		len++;
	if (str[len] == sd_quote)
		return (len + 1);
	else
		return (-1);
}

// int	len_quotes(char *str, char sd_quote)
// {
// 	int	len;

// 	len = 1;
// 	while (str[len] && str[len] != sd_quote)
// 		len++;
// 	return (len);
// }

char	*prs_tokens_join(t_token *token)
{
	char	*res;

	res = ft_strdup("");
	while (token != NULL)
	{
		if (token->value != NULL)
		{
			res = chk_null_strjoin(res, token->value);
			if (!res)
				break ;
		}
		token = token->next;
	}
	return (res);
}

t_token	*remove_empty_tokens(t_token *head)
{
	t_token	*current;
	t_token	*prev;
	t_token	*next;

	current = head;
	prev = NULL;
	while (current != NULL)
	{
		next = current->next;
		if (current->value == NULL || current->value[0] == '\0')
		{
			if (prev == NULL)
				head = next;
			else
				prev->next = next;
			if (current->value)
				free(current->value);
			free(current);
		}
		else
			prev = current;
		current = next;
	}
	return (head);
}
