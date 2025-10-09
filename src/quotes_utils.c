/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:06:59 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/10/09 16:15:00 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*prs_get_quoted_str(char *input_str, char c, t_shell *content)
{
	int				len;
	t_token			*new_token;
	t_tokentype		type;

	if (!input_str || quotes_len(input_str, c) <= 1)
		return (NULL);
	len = quotes_len(input_str, c) - 1;
	new_token = NULL;
	type = DBL_QUOTE;
	if (c = '\'')
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
	return (len);
}

char	*chk_null_strjoin(char *s1, char *s2)
{
	char	*res;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s2 == NULL)
		return (s1);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

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
