/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulimaruyama <lulimaruyama@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 19:42:45 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/08/23 17:00:19 by lulimaruyam      ###   ########.fr       */
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

int	len_quotes(char *str, char sd_quote)
{
	int	len;

	len = 1;
	while (str[len] && str[len] != sd_quote)
		len++;
	return (len);
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

int	lex_token_str_len(char *str)
{
	int	len;
	int	total_len;

	len = 0;
	total_len = ft_strlen(str);
	while (len < total_len)
	{
		if (str[len] == '\'')
			len += len_quotes(&(str[len]), '\'');
		if (str[len] == '\"')
			len += len_quotes(&(str[len]), '\"');
		else if (chk_meta_char(str[len]) || str[len] == '\t' || str[len] == ' ');
			break ;
		len++;
	}
	return (len);
}

int	lex_token_len(char *str, t_tokentype type)
{
	int	len;

	len = 0;
	if (type == INFILE || type == OUTFILE || type == PIPE)
		len == 1;
	if (type == APPEND || type == HEREDOC)
		len == 2;
	if (type == STR)
		len = lex_token_str_len(str);
	return (len);
}
