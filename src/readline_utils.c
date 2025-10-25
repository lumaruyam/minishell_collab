/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:15:35 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/25 20:29:26 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_multiline_input(char *first_line)
{
	char	*input;
	char	*temp;
	char	*line;

	input = ft_strdup(first_line);
	if (!input)
		return (NULL);
	while (has_unclosed_quotes(input))
	{
		temp = input;
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n", 2);
			free(input);
			return (NULL);
		}
		input = ft_strjoin(temp, "\n");
		free(temp);
		temp = input;
		input = ft_strjoin(temp, line);
		free(temp);
		free(line);
	}
	return (input);
}

// char	*read_multiline_input(t_shell *content, char *first_line)
// {
// 	char	*input;
// 	char	*temp;
// 	char	*line;

// 	input = ft_strdup(first_line);
// 	if (!input)
// 		return (NULL);

// 	while (has_unclosed_quotes(input))
// 	{
// 		temp = input;
// 		line = readline("> ");
// 		if (!line)
// 		{
// 			ft_putstr_fd("minishell: unexpected EOF while looking for matching quote\n", 2);
// 			free(input);
// 			return (NULL);
// 		}
// 		input = ft_strjoin(temp, "\n");
// 		free(temp);
// 		temp = input;
// 		input = ft_strjoin(temp, line);
// 		free(temp);
// 		free(line);
// 	}
// 	return (input);
// }

int	has_unclosed_quotes(char *str)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (str[i] == '\\' && in_quote != '\'')
		{
			i++;
			if (str[i] == '\0')
				break ;
		}
		else if ((str[i] == '\'' || str[i] == '\"') && in_quote == 0)
			in_quote = str[i];
		else if (str[i] == in_quote)
			in_quote = 0;
		i++;
	}
	return (in_quote != 0);
}
