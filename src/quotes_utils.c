/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:06:59 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/24 17:43:28 by lulimaruyam      ###   ########.fr       */
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
