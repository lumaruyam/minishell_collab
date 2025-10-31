/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 16:08:04 by lulimaruyam       #+#    #+#             */
/*   Updated: 2025/10/31 12:38:00 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env_id(char *input_line)
{
	char	*at_equal;
	int		len;

	if (!input_line)
		return (NULL);
	at_equal = ft_strchr(input_line, '=');
	if (!at_equal)
		return (ft_strdup(input_line));
	if (at_equal == input_line)
		return (NULL);
	len = at_equal - input_line;
	return (ft_substr(input_line, 0, len));
}

// char	*get_env_id(char *input_line)
// {
// 	char	*at_equal;

// 	if (!input_line)
// 		return (NULL);
// 	at_equal = ft_strchr(input_line, '=');
// 	if (!at_equal)
// 		return (ft_strdup(input_line));
// 	else if (at_equal - input_line == 0)
// 		return (NULL);
// 	return (ft_strdup(input_line + (at_equal - input_line)));
// }

char	*get_env_value(char *input_line)
{
	char	*at_equal;

	if (!input_line)
		return (NULL);
	at_equal = ft_strchr(input_line, '=');
	if (!at_equal)
		return (NULL);
	return (ft_strdup(at_equal + 1));
}

t_env	*env_make(char *env_id, char *env_value, char *env_line)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (free(env_id), free(env_value), free(env_line), NULL);
	new->id = env_id;
	new->value = env_value;
	new->env_line = env_line;
	new->next = NULL;
	return (new);
}

int	env_add_back(t_env **head, t_env *new)
{
	t_env	*cur;

	if (*head == NULL)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
	}
	return (SUCCESS);
}

void	env_free(t_env *env)
{
	t_env	*tmp_next;

	while (env)
	{
		tmp_next = env->next;
		if (env->id)
			free(env->id);
		if (env->value)
			free(env->value);
		if (env->env_line)
			free(env->env_line);
		free(env);
		env = tmp_next;
	}
}
