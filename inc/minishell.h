/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:07:25 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/06/12 20:59:40 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_shell
{
	int	std_in; //Stores the default input file descriptor (usually STDIN_FILENO)
	int	std_out; //Stores the default output file descriptor (usually STDOUT_FILENO)
	// add exit code?
	// add pid?
	// add execution?
	//int	ct_pid;
	//int	ct_exec;
	t_env	*env;
}	t_shell;

typedef struct s_env
{
	char	*env; //name or key of the environment variable (e.g., "PATH")
	char	*value; //value of the environment variable
	char	*env_line; //The full string representation "NAME=value"
	t_env	*next; //ointer to the next environment variable in the list
}	t_env;

#endif
