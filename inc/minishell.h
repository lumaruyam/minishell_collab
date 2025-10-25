/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:07:25 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/25 17:25:48 by lulmaruy         ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"

# define SUCCESS 0
# define FAIL 1
# define FAIL_VOID 2 //put in enum
# define FAIL_BUILD -1

# define PROMPT_NAME "minishell"

# define CMD_NOT_FOUND 127
# define SIG_OFFSET 128
# define MAX_FDS 1024

# define DEFAULT_ENV "MINISHELL=minishell"

typedef struct s_exec		t_exec;
typedef struct s_env		t_env;
typedef struct s_token		t_token;
typedef struct s_arg		t_arg;
typedef struct s_filename	t_filename;
typedef enum e_tokentype	t_tokentype;

typedef struct s_shell
{
	int				std_in; //Stores the default input file descriptor
	int				std_out; //Stores the default output file descriptor
	unsigned char	exit_code; // stores the shell’s last exit status
	pid_t			*pids;// array of process IDs for child processes
	t_exec			*exec; // linked list of commands to be executed
	int				ct_pid;// count of currently active pids
	int				ct_exec;// count of exec blocks (commands)
	t_env			*env;
	int				last_exit_status;
	bool			is_child_process;
	bool			child_end_with_signal;
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
	char		*value;// token string (e.g., "ls", "|", "file.txt")
	t_shell		*content;// reference to the shell context
	t_tokentype	type;// type of token (e.g., CMD, ARG, PIPE)
	t_token		*next;// pointer to next token in the list
}	t_token;

typedef struct s_filename
{
	char		*path;// file path or name (e.g., "output.txt")
	t_tokentype	type;// type of redirection (INFILE, OUTFILE, etc.)
	t_filename	*next;// pointer to next file in the redirection list
}	t_filename;

typedef struct s_exec
{
	char			*cmd;// command name (e.g., "ls")
	t_arg			*args;// linked list of arguments for the command
	t_filename		*redirs;// linked list of redirection files
	struct s_exec	*next;// pointer to next command in pipeline
	int				fd_in;// input file descriptor for the command
	int				fd_out;// output file descriptor for the command
}	t_exec;

extern volatile sig_atomic_t	g_signal;

// typedef struct s_signal DONT USE THISS!!!!!
// {
// 	int	end_heredoc;
// 	int	signal_code;
// }	t_signal;

// extern t_signal		g_signal;

/* ------------------------------Main----------------------------------- */

/*main (shell)*/
int			read_loop(t_shell *content);
t_shell		*init_shell(char *env[]);
int			process_input(t_shell *content, char *line);
int			init_exec(t_shell *content, t_token **token);
t_env		*dup_env(char *env[]);
int			chk_empty_line(char *line);
int			handle_eof(char *line);

/*env*/
t_env		*env_make(char *env_id, char *env_value, char *env_line);

void		signals_heredoc(int status);
t_env		*set_default_env(void);
char		*get_env_id(char *input_line);
char		*get_env_value(char *input_line);
int			env_add_back(t_env **head, t_env *new);
void		env_free(t_env *env);
void		env_delete_1node(t_env *env);

/*main free*/
void		free_shell(t_shell *content);
void		free_after_process(t_shell *content, t_token *token);

/* -----------------------------Lexing---------------------------------- */

/*lexing*/
t_token		*lex_tokenize_wd(char *str, t_shell *content);
t_token		*lexing(t_shell *content, char *input_line);

/*lexing helper*/
t_tokentype	lex_get_tokentype(char *input_str);
int			lex_token_len(char *str, t_tokentype type);
int			lex_token_str_len(char *str);
int			chk_meta_char(char c);

/*token*/
t_token		*create_token(char *token_value, int n, t_tokentype type,
				t_shell *content);
int			token_add_back(t_token **head, t_token *new_token);
void		token_free(t_token *head);
t_token		*remove_empty_tokens(t_token *head);

/* -----------------------------Signals--------------------------------- */
void		signal_child_process(void);
void		init_signal_heredoc(void);
void		init_ignore_signal(void);
void		signal_to_action(t_shell *data);
int			sig_exit(void);
void		init_signal_exec(void);
void		init_signal_exec(void);
void		init_signal_interactive_mode(void);
void		sigint_exec(int status);

/* -----------------------------Parsing--------------------------------- */

/*parsing*/
int			parsing(t_token **token);
int			prs_chk_allnodes_null(t_token *token);
int			prs_remove_node_null(t_token **head);
void		prs_unlink_error(t_token *token);

/*parsing helper*/
char		*prs_tokens_join(t_token *token);
char		*chk_null_strjoin(char *s1, char *s2);

/* -----------------------------Expansion------------------------------- */

/*expand*/
int			prs_ct_dollars(char *input_str);
char		*prs_expand_1envvar(char *str, char *envvar_found,
				t_shell *content);
int			prs_envvar_expand(t_token *token);

/*expand env*/
int			ft_envvar_len(char *envvar);
char		*get_envvar_name(char *envvar);
char		*get_str_before_envvar(char *full_str, char *envvar);
char		*get_str_after_envvar(char *envvar);
char		*get_envvar_value(char *envvar, t_shell *content);
t_env		*get_env(char *env_id, t_env *env);

/*expand utils*/
char		*handle_qmark_exit(t_shell *content);
char		*handle_dollar_pid(void);
int			prs_expand_env(t_token *token);

/* -----------------------------heredoc------------------------------- */

int			prs_handle_redir(t_token *token);
int			prs_handle_heredoc(t_token *token);
int			prs_init_heredoc(int fd, char *eof_delimiter);

/* ------------------------------quotes------------------------------- */

/*quotes*/
int			prs_chk_quotes(t_token *token);
t_token		*prs_quotes_to_tokens(char *input_str, t_shell *content);
int			prs_quotes_n_expand_env(t_token(*token));

/*quotes utils*/
t_token		*prs_get_quoted_str(char *input_str, char c,
				t_shell *content);
int			len_quotes(char *str, char sd_quote);
int			rogue_len(char *str);

/*readline utils*/
char	*read_multiline_input(char *first_line);
int		has_unclosed_quotes(char *str);

/* -----------------------------build to exec------------------------- */

/*build to exec*/
t_exec		*build_to_exec(t_token *token);
t_exec		*init_build(void);
int			bd_handle_pipe(t_exec *exec, t_token *token);
int			bd_handle_cmd(t_exec *exec, t_token *token);

/*build utils*/
int			ft_build_lstsize(t_exec *exec);
void		build_free_all(t_exec *exec);

/*build args*/
int			bd_handle_args(t_exec *exec, t_token *token);
t_arg		*bd_make_args(char *arg_value);
int			arg_add_back(t_arg **head, t_arg *new);
void		arg_free(t_arg *args);

/*build filenames*/
int			bd_handle_redirs(t_exec *exec, t_token *token);
t_filename	*bd_make_filenames(char *pathname, t_tokentype type);
int			filename_add_back(t_filename **head, t_filename *new);
void		filename_free(t_filename *filename);

/* -----------------------------builtins--------------------------- */

/* Builtins Handler*/
int			check_is_builtin(char *input_cmd);
int			exec_builtin(t_shell *content, char *input_cmd,
				t_arg *args);

/* Builtins env*/
int			chk_envid_valid(char *env_id);
int			add_envvar(char *input_line, t_env **env_head);
void		update_envvar(t_env *update_env, char *env_line);

/** ft_env / ft_pwd */
int			ft_env(t_shell *content, t_arg *args);
int			ft_pwd(t_arg *args);

/* ft_echo*/
int			ft_echo(t_arg *args);

/* ft_exit*/
int			ft_exit(t_shell *content, t_arg *args);
int			chk_exitcode(char *input_line);

/* ft_cd */
int			ft_cd(t_shell *content, t_arg *args);
int			update_pwd(t_shell *content, char *oldpwd_value);
int			ft_arg_lstsize(t_arg *args);

/* ft_export */
int			ft_export(t_shell *content, t_arg *args);
int			export_print_sorted_env(t_env *env);
char		**sort_env_arrs(char **env_arrs);

/* ft_unset */
int			ft_unset(t_shell *content, t_arg *args);
int			delete_envvar(char *env_id, t_env **env);
void		env_delete_1node(t_env *env);

/* builtins error1,2 */
void		error_env(char *option);
void		error_pwd(char *option);
void		error_exit(char *input_line);
void		error_cd(int err_n, char *pathname);
void		error_export(char *input_line);

/* ft_arrys_utils*/
char		**ft_arrsdup(char **src_arrs);
void		arrs_free(char **arrs);
int			ft_arrslen(char **arrs);

/* -----------------------------execs--------------------------- */

int			exec(t_shell *content);

/* execs family */
int			exec_parent(t_shell *content);
void		child_process(t_shell *content, int (*fd)[2],
				int i, t_exec *tmp);

/* execs redirs */
int			redirs_type(t_filename *file);
int			err_redirs(t_exec *exec, t_shell *content);

/* execs execution */
char		**env_format(t_env *env);
int			check_is_alr_path(char *cmd);
char		*find_path(char *cmd, t_env *env);
int			ft_execution(t_shell *content, t_exec *tmp);
/* execs err */
void		err_open(int err_no, char *file);
int			err_pipe(int err_no, t_shell *content);
void		exe_err_coredump(int pid);
int			err_fork(int err_no, t_shell *ctx, int fd[][2]);
void		err_execve(char *path, int err_no);
void		ft_free_all(char **arr);

/* execs utils1,2,3 */
void		exe_close(int *fd);
void		ft_close(t_shell *content);
void		close_fds(int pipe_nb, int (*fd)[2], int cur_cmd,
				bool is_final_close);
int			ft_env_lstsize(t_env *env);

int			open_pipes(int pipe_nb, int (*fd)[2]);
void		set_std(t_shell *content, int mode);
void		close_all(int pipe_nb, int (*fd)[2]);
void		unlink_all(t_shell *content);
void		wait_children(int ct_pid, t_shell *content);

int			ft_args_lstsize(t_arg *args);
void		exec_args_create(t_exec *temp, int args_nb,
				char *args[args_nb]);
int			ft_char_count(char *str, char c);
void		ft_free_all(char **arr);
int			check_is_alr_path(char *cmd);

#endif
