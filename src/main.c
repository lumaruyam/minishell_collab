/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 20:33:25 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/26 16:41:49 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_input(void)
{
	char	*line;

	if (isatty(STDIN_FILENO))
	{
		line = readline("minishell> ");
		if (line && *line)
			add_history(line);
	}
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
	}
	return (line);
}

int	read_loop(t_shell *content)
{
	char	*line;

	(void)content;
	line = NULL;
	while (1)
	{
		init_signal_interactive_mode();
		line = get_input();
		if (handle_eof(line))
			break ;
		if (chk_empty_line(line) == 0)
		{
			add_history(line);
			if (process_input(content, line) != 0)
				ft_putendl_fd("Syntax Error", 2), content->exit_code = 2;
		}
		signal_to_action(content);
		if (line)
			free(line);
		line = NULL;
	}
	if (line)
		free(line);
	return (0);
}

//removed to debug ./minishell | ./minishell
// int	read_loop(t_shell *content)
// {
// 	char	*line;

// 	(void)content;
// 	line = NULL;
// 	while (1)
// 	{
// 		init_signal_interactive_mode();
// 		line = readline("minishell> ");
// 		if (handle_eof(line))
// 			break ;
// 		if (chk_empty_line(line) == 0)
// 		{
// 			add_history(line);
// 			if (process_input(content, line) != 0)
// 				ft_putendl_fd("Syntax Error", 2), content->exit_code = 2;
// 		}
// 		signal_to_action(content);
// 		if (line)
// 			free(line);
// 		line = NULL;
// 	}
// 	if (line)
// 		free(line);
// 	return (0);
// }

// removed to debug leak 1026
// int	read_loop(t_shell *content)
// {
// 	char	*line;

// 	(void)content;
// 	line = NULL;
// 	while (1)
// 	{
// 		init_signal_interactive_mode();
// 		line = readline("minishell> ");
// 		if (handle_eof(line))
// 			break ;
// 		else if (chk_empty_line(line) == 0)
// 		{
// 			add_history(line);
// 			if (process_input(content, line) != 0)
// 			{
// 				ft_putendl_fd("Syntax Error", 2);
// 				content->exit_code = 2;
// 			}
// 			line = NULL;
// 		}
// 		signal_to_action(content);
// 		if (line)
// 			free(line);
// 	}
// 	return (0);
// }

int	main(int ac, char *av[], char **env)
{
	t_shell	*content;

	content = NULL;
	(void)ac;
	(void)av;
	content = init_shell(env);
	if (!content)
		return (EXIT_FAILURE);
	read_loop(content);
	free_shell(content);
	rl_clear_history();
	ft_putendl_fd("exit", 2);
	return (EXIT_SUCCESS);
}

/*signal before modified
int	read_loop(t_shell *content)
{
	char	*line;

	(void)content;
	line = NULL;
	while (1)
	{
		init_signals();
		line = readline("minishell> ");
		if (!line)
			break ;
		else if (chk_empty_line(line) == 0)
		{
			add_history(line);
			if (process_input(content, line) != 0)
			{
				ft_putendl_fd("Syntax Error", 2);
				content->exit_code = 2;
			}
			line = NULL;
		}
		if (line)
			free(line);
	}
	return (0);
}*/
