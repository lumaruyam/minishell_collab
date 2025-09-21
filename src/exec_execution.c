
#include "../inc/minishell.h"

//I did env_format function as it is needed for builtin Luli

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
			arrs_free(env_arr);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

