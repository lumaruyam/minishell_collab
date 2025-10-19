/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 17:45:42 by skoudad           #+#    #+#             */
/*   Updated: 2025/10/19 17:02:12 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	exec_args_create(t_exec *tmp, int args_nb, char **args);
static int	handle_exec_error(char *path, char **env, char **args);

char	**env_format(t_env *env)
{
	char	**env_arr;
	int		size;
	int		i;

	size = ft_env_lstsize(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_arr)
		return (NULL);
	i = 0;
	while (i < size && env)
	{
		env_arr[i] = ft_strdup(env->env_line);
		if (!env_arr[i])
		{
			ft_free_all(env_arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	check_is_alr_path(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
static char	*get_exec_path(char **paths, char *cmd)
{
	char	*path;
	char	*exec;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		exec = ft_strjoin(path, cmd);
		free(path);
		if (!access(exec, X_OK | F_OK))
		{
			ft_free_all(paths);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_all(paths);
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	**paths;

	if (cmd && cmd[0] == '\0')
		return (NULL);
	if (!env || check_is_alr_path(cmd) == 1)
		return (ft_strdup(cmd));
	while (env && ft_strncmp("PATH=", env->env_line, 5) != 0)
		env = env->next;
	if (!env)
		return (ft_strdup(cmd));
	paths = ft_split(env->value, ':');
	return (get_exec_path(paths, cmd));
}

int	ft_execution(t_shell *content, t_exec *temp)
{
	int		args_nb;
	char	*path;
	char	**args;
	char	**env;

	if (!temp->cmd)
		return (0);
	path = find_path(temp->cmd, content->env);
	if (!path)
		return (err_execve(temp->cmd, errno), 127);
	env = env_format(content->env);
	if (!env)
		return (free(path), 127);
	args_nb = ft_arg_lstsize(temp->args) + 2;
	args = malloc(sizeof(char *) * args_nb);
	if (!args)
		return (free(path), ft_free_all(env), 127);
	exec_args_create(temp, args_nb, args);
	if (execve(path, args, env) == -1)
		return (handle_exec_error(path, env, args));
	free(path);
	ft_free_all(env);
	free(args);
	return (0);
}

static void	exec_args_create(t_exec *tmp, int args_nb, char **args)
{
	int	i;
	t_arg	*cur;

	i = 0;
	args[i++] = ft_strdup(tmp->cmd);
	cur = tmp->args;
	while (cur && i < args_nb - 1)
	{
		args[i++] = ft_strdup(cur->value);
		cur = cur->next;
	}
	args[i] = NULL;
}

static int	handle_exec_error(char *path, char **env, char **args)
{
	int i;
	int rc;

	err_execve(path, errno);
	if (env)
		ft_free_all(env);
	if (args)
	{
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
	}
	if (errno == ENOENT)
		rc = 127;
	else if (errno == EACCES)
		rc = 126;
	else
		rc = 1;
	return (rc);
}
