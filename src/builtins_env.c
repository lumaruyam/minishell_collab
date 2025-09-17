/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 18:59:02 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/09/17 19:04:16 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/builtins.h"

int	add_envvar(char *input_line, t_env **env_head)
{
	char	*env_id;
	char	*dup_inputline;
	t_env	*env;

	env_id = get_env_id(input_line);
	env = get_env(env_id, *env_head);
}
