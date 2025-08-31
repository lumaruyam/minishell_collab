/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:07:25 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/08/31 17:53:41 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

# define SUCCESS 0
# define FAIL 1
# define FAIL_VOID 2
# define FAIL_BUILD -1

# define SIG_OFFSET 128

# define DEFAULT_ENV "MINISHELL=minishell"

typedef struct s_shell
{
	int	std_in; //Stores the default input file descriptor (usually STDIN_FILENO)
	int	std_out; //Stores the default output file descriptor (usually STDOUT_FILENO)
	unsigned char	exit_code; // stores the shell’s last exit status
	pid_t	*pids;// array of process IDs for child processes
	t_exec	*exec; // linked list of commands to be executed
	int	ct_pid;// count of currently active pids
	int	ct_exec;// count of exec blocks (commands)
	t_env	*env;
}	t_shell;

typedef struct s_env
{
	char	*id; //name or key of the environment variable (e.g., "PATH")
	char	*value; //value of the environment variable
	char	*env_line; //The full string representation "NAME=value"
	t_env	*next; //pointer to the next environment variable in the list
}	t_env;

typedef struct s_arg
{
	char	*value;// argument value (e.g., "ls", "-l", "file.txt")
	t_arg	*next;// pointer to next argument in the list
}	t_arg;

typedef enum e_tokentype
{
	INFILE,// "<" — input redirection
	OUTFILE,// ">" — output redirection (overwrite)
	HEREDOC, // "<<" — here-document input
	NON_HEREDOC,// non-heredoc input (used internally)
	APPEND,// ">>" — output redirection (append)
	PIPE,// "|" — pipe to next command
	STR,// regular string
	SGL_QUOTE,// single-quoted string
	DBL_QUOTE,// double-quoted string
	CMD,// command keyword
	FILENAME, // file name in redirection
	ARG,// argument to a command
}	t_tokentype;

typedef struct s_token
{
	char	*value;// token string (e.g., "ls", "|", "file.txt")
	t_shell	*content;// reference to the shell context
	t_tokentype	type;// type of token (e.g., CMD, ARG, PIPE)
	t_token	*next;// pointer to next token in the list
}	t_token;

typedef struct s_filename
{
	char	*path;// file path or name (e.g., "output.txt")
	t_tokentype	type;// type of redirection (INFILE, OUTFILE, etc.)
	t_filename	*next;// pointer to next file in the redirection list
}	t_filename;

typedef struct s_exec
{
	char	*cmd;// command name (e.g., "ls")
	t_arg	*args;// linked list of arguments for the command
	t_filename	*redirs;// linked list of redirection files
	struct s_exec	*next;// pointer to next command in pipeline
	int	fd_in;// input file descriptor for the command
	int	fd_out;// output file descriptor for the command
}	t_exec;

typedef struct s_signal//might not pass the evaluation
{
	int	end_heredoc;
	int	signal_code;
}	t_signal;

extern t_signal	g_signal;//might not pass the evaluation


void	signals_heredoc(int status);

#endif
