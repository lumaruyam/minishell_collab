/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoudad <skoudad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:19:57 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/19 17:02:12 by skoudad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **ft_arrsdup(char **arr);

static	void ft_swap_ptr(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char	**sort_env_arrs(char **env_arrs)
{
	char	**res;
	int		i;
	int		j;

	res = ft_arrsdup(env_arrs);
	if (!res)
		return (NULL);
	i = 0;
	while (res[i])
	{
		j = i + 1;
		while (res[j])
		{
			if (ft_strcmp(res[i], res[j]) > 0)
				ft_swap_ptr(&res[i], &res[j]);
			j++;
		}
		i++;
	}
	return (res);
}

static void print_export_all(char **sorted)
{
	int		i;
	char	*tmp_value;
	char	*tmp_id;

	i = 0;
	while (sorted[i])
	{
		printf("export ");
		tmp_value = ft_strchr(sorted[i], '=');
		if (!tmp_value)
			printf("%s\n", sorted[i]);
		else
		{
			tmp_value += 1;
			tmp_id = get_env_id(sorted[i]);
			printf("%s=\"%s\"\n", tmp_id, tmp_value);
			free(tmp_id);
		}
		i++;
	}
}

int	export_print_sorted_env(t_env *env)
{
	char	**env_arrs;
	char	**sorted;

	env_arrs = env_format(env);
	if (!env_arrs)
		return (FAIL);
	sorted = sort_env_arrs(env_arrs);
	if (!sorted)
		return (ft_free_all(env_arrs), FAIL);
	print_export_all(sorted);
	ft_free_all(sorted);
	ft_free_all(env_arrs);
	return (SUCCESS);
}

int	ft_export(t_shell *content, t_arg *args)
{
	if (!args)
	{
		if (export_print_sorted_env(content->env) != 0)
			return (SUCCESS);
	}
	else
	{
		while(args)
		{
			if (add_envvar(args->value, &(content->env)) != 0)
				return (FAIL);
			args = args->next;
		}
	}
	return (SUCCESS);
}

static char **ft_arrsdup(char **arr)
{
	int i;
	char **res;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		res[i] = ft_strdup(arr[i]);
		if (!res[i])
		{
			ft_free_all(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}



