/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:46:21 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/10/24 18:15:33 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_chk_quotes(t_token *token)
{
	int		i;
	char	*str;
	int		quote_len;

	while (token && token->type == STR)
	{
		i = 0;
		str = token->value;
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
			{
				quote_len = len_quotes(&str[i], str[i]);
				if (quote_len == -1)
					return (FAIL);
				i += quote_len;
			}
			else
				i++;
		}
		token = token->next;
	}
	return (SUCCESS);
}

static t_token	*process_single_token(char *str, t_shell *content, int *i)
{
	t_token	*new_token;

	if (str[0] == '\'' || str[0] == '\"')
	{
		new_token = prs_get_quoted_str(str, str[0], content);
		if (!new_token)
		{
			new_token = create_token("", 0, STR, content);
			*i += 1;
		}
		else
			*i += ft_strlen(new_token->value) + 1;
	}
	else
	{
		new_token = create_token(str, rogue_len(str), STR, content);
		*i += ft_strlen(new_token->value) - 1;
	}
	return (new_token);
}

t_token	*prs_quotes_to_tokens(char *input_str, t_shell *content)
{
	int		i;
	t_token	*token;
	t_token	*new_token;

	i = 0;
	token = NULL;
	while (input_str[i])
	{
		new_token = process_single_token(&(input_str[i]), content, &i);
		if (!new_token)
			return (NULL);
		token_add_back(&token, new_token);
		i++;
	}
	return (token);
}

int	prs_quotes_n_expand_env(t_token *token)
{
	t_token	*input_str;

	while (token != NULL)
	{
		if (token->type == STR)
		{
			input_str = prs_quotes_to_tokens(token->value, token->content);
			prs_expand_env(input_str);
			if (token->value)
				free(token->value);
			token->value = prs_tokens_join(input_str);
			token_free(input_str);
		}
		token = token->next;
	}
	return (SUCCESS);
}

// int	prs_chk_quotes(t_token *token)
// {
// 	int		i;
// 	char	*str;

// 	while (token != NULL)
// 	{
// 		if (token->type == STR)
// 		{
// 			i = 0;
// 			str = token->value;
// 			while (str[i])
// 			{
// 				if (str[i] == '\'' || str[i] == '\"')
// 					i += len_quotes(&(str[i]), str[i]);
// 				if (str[i] == '\0')
// 					return (FAIL);
// 				i++;
// 			}
// 		}
// 		token = token->next;
// 	}
// 	return (SUCCESS);
// }
