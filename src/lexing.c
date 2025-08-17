/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:12:40 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/17 19:38:01 by lulimaruyam      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*lex_tokenize_wd(char *str, t_shell *content)
{
	t_token		*new;
	t_tokentype	type;
	int			token_len;

	new = NULL;
	type = lex_get_tokentype(str);
	token_len = lex_token_len(str, type);
	new = make_token(str, token_len, type, content);
	return (new);
}

t_token	*lexing(t_shell content, char *input_line)
{
	t_token	*token;
	t_token *cur;
	int		i;

	i = 0;
	token = NULL;
	while (input_line[i])
	{
		if (input_line[i] == ' ' || input_line[i] == '\t')
			i++;
		else
		{
			cur = lex_tokenize_wd(&(input_line[i]), content);
			if (!cur)
			{
				token_free(token);
				return (NULL);
			}
			token_add_back(&token, cur);
			i += ft_strlen(cur->value);
		}
	}
	return (token);
}
