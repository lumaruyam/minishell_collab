/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:42:45 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/10/22 21:47:30 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_tokentype	lex_get_tokentype(char *input_str)
{
	if (input_str[0] == '>')
	{
		if (input_str[1] == '>')
			return (APPEND);
		else
			return (OUTFILE);
	}
	else if (input_str[0] == '<')
	{
		if (input_str[1] == '<')
			return (HEREDOC);
		else
			return (INFILE);
	}
	else if (input_str[0] == '|')
		return (PIPE);
	return (STR);
}

int	chk_meta_char(char c)
{
	int	found;

	found = 0;
	if (c == '|')
		found = 1;
	else if (c == '<')
		found = 2;
	else if (c == '>')
		found = 3;
	else if (c == '\"')
		found = 4;
	else if (c == '\'')
		found = 5;
	return (found);
}

// int	lex_token_str_len(char *str)
// {
// 	int	len;
// 	int	total_len;

// 	len = 0;
// 	total_len = ft_strlen(str);
// 	while (len < total_len)
// 	{
// 		if (str[len] == '\'')
// 			len += len_quotes(&(str[len]), '\'');
// 		if (str[len] == '\"')
// 			len += len_quotes(&(str[len]), '\"');
// 		else if (chk_meta_char(str[len]) || str[len] == '\t' || str[len] == ' ')
// 			break ;
// 		len++;
// 	}
// 	return (len);
// }

int	lex_token_str_len(char *str)
{
	int	len;
	int	total_len;
	int	quote_len;

	len = 0;
	total_len = ft_strlen(str);
	while (len < total_len)
	{
		if (str[len] == '\'' || str[len] == '\"')
		{
			quote_len = len_quotes(&(str[len]), str[len]);
			if (quote_len == -1)
			{
				len = total_len;
				break ;
			}
			len += quote_len;
		}
		else if (chk_meta_char(str[len]) || str[len] == '\t' || str[len] == ' ')
			break ;
		else
			len++;
	}
	return (len);
}

int	lex_token_len(char *str, t_tokentype type)
{
	int	len;

	len = 0;
	if (type == INFILE || type == OUTFILE || type == PIPE)
		len = 1;
	else if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == STR)
		len = lex_token_str_len(str);
	return (len);
}
