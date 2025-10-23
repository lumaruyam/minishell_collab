/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 14:41:10 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/23 21:11:00 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	prs_handle_redir(t_token *token)
{
	if (token && token->type == PIPE)
		return (FAIL);
	while (token)
	{
		if (token->type == INFILE || token->type == OUTFILE
			|| token->type == HEREDOC || token->type == APPEND)
		{
			if (token->next == NULL || token->next->type != STR)
				return (FAIL);
			token->next->type = FILENAME;
		}
		else if (token->type == PIPE && token->next == NULL)
			return (FAIL);
		token = token->next;
	}
	return (SUCCESS);
}

static char	*create_random_filename(char *str)
{
	char			*new;
	int				i;
	unsigned long	rand;

	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * 17);
	if (!new)
		return (NULL);
	i = 0;
	while (i < 8)
	{
		new[i] = "/tmp/hd_"[i];
		i++;
	}
	rand = (unsigned long)str;
	i = 8;
	while (i < 16)
	{
		rand = rand * 1103515245 + 12345;
		new[i] = 'a' + (rand % 26);
		i++;
	}
	new[16] = '\0';
	return (new);
}

static int	process_heredoc_input(int fd, char *eof_delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			ft_putstr_fd("here_doc: delimited by end-of-file\n", 2);
			break ;
		}
		if (g_signal != 0)
		{
			free(line);
			return (1);
		}
		if (ft_strcmp(line, eof_delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}

// static int	process_heredoc_input(int fd, char *eof_delimiter)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		line = readline("heredoc> ");
// 		if (!line)
// 		{
// 			if (g_signal == 0)
// 				ft_putstr_fd("here_doc: delimited by end-of-file\n", 2);
// 			break ;
// 		}
// 		if (g_signal != 0)
// 		{
// 			free(line);
// 			return (1);
// 		}
// 		if (ft_strcmp(line, eof_delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		ft_putendl_fd(line, fd);
// 		free(line);
// 	}
// 	return (0);
// }

int	prs_init_heredoc(int fd, char *eof_delimiter)
{
	int	signal_received;

	init_signal_heredoc();
	signal_received = process_heredoc_input(fd, eof_delimiter);
	if (signal_received)
	{
		g_signal = 0;
		return (1);
	}
	return (0);
}

int	prs_handle_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token != NULL && end == 0)
	{
		if (token->type == HEREDOC)
		{
			filename = create_random_filename(token->next->value);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (FAIL);
			if (prs_init_heredoc(fd, token->next->value) != 0)
				end = 1;
			close(fd);
			free(token->next->value);
			token->next->value = filename;
			token->type = NON_HEREDOC;
		}
		token = token->next;
	}
	return (end);
}


/* signals not modified
int	prs_init_heredoc(int fd, char *eof_delimiter)
{
	char	*line;

	signal(SIGINT, signals_heredoc);//signals to review
	while (1)
	{
		line = readline("heredoc>");
		if (!line)
		{
			ft_putstr_fd("here_doc: called end-of-line (ctrl-d)\n", 2);
			break ;
		}
		if (ft_strcmp(line, eof_delimiter) == 0 || g_signal.end_heredoc == 1)//signal
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (init_heredoc_signal());//signals to review
}

static int init_heredoc_signal(void)
{
	if (g_signal.end_heredoc = 1)
	{
		g_signal.end_heredoc = 0;
		return (FAIL);
	}
	return (SUCCESS);
}*/

// int	prs_handle_heredoc(t_token *token)
// {
// 	char	*filename;
// 	int		fd;
// 	int		end;

// 	end = 0;
// 	while (token != NULL && end == 0)
// 	{
// 		if (token->type == HEREDOC)
// 		{
// 			filename = create_random_filename(token->next->value);
// 			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 				return (FAIL);
// 			if (prs_init_heredoc(fd,token->next->value) != 0)
// 				end = 1;
// 			close(fd);
// 			free(token->next->value);
// 			token->next->value = filename;
// 			token->type = NON_HEREDOC;
// 		}
// 		token = token->next;
// 	}
// 	return (end);
// }

// int	prs_init_heredoc(int fd, char *eof_delimiter)
// {
// 	char	*line;

// 	init_signal_heredoc();
// 	while (1)
// 	{
// 		line = readline("heredoc>");
// 		if (!line)
// 		{
// 			ft_putstr_fd("here_doc: called end-of-line (ctrl-d)\n", 2);
// 			break ;
// 		}
// 	if (ft_strcmp(line, eof_delimiter) == 0 || rl_done)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd, line, ft_strlen(line));
// 		write(fd, "\n", 1);
// 		free(line);
// 	}
// 	init_signal_heredoc();
// 	return (0);
// }
