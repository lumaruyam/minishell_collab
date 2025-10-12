/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrys_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lulmaruy <lulmaruy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:19:30 by lulmaruy          #+#    #+#             */
/*   Updated: 2025/10/12 15:43:41 by lulmaruy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	arrs_free(char **arrs)
{
	int	i;

	i = 0;
	while (arrs[i])
	{
		free(arrs[i]);
		i++;
	}
	free(arrs);
}

int	ft_arrslen(char **arrs)
{
	int	len;

	len = 0;
	while (arrs[len])
		len++;
	return (len);
}

char	**ft_arrsdup(char **src_arrs)
{
	char	**res;
	int		srclen;
	int		i;

	srclen = ft_arrslen(src_arrs);
	res = malloc(sizeof(char *) * (srclen + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (src_arrs[i])
	{
		res[i] = ft_strdup(src_arrs[i]);
		if (!res[i])
		{
			arrs_free(res);
			return (NULL);
		}
		i++;
	}
	res[i] = NULL;
	return (res);
}
