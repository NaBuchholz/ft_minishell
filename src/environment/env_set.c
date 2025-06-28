/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 12:44:50 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/28 12:47:05 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	validate_env_params(char ***env, char *name)
{
	if (!env || !*env || !name || !*name)
		return (-1);
	return (0);
}

static int	update_existing_var(char **env, int index, char *name, char *value)
{
	free(env[index]);
	env[index] = create_env_string(name, value);
	if (!env[index])
		return (-1);
	return (0);
}

static char	**create_expanded_env(char **env, int count)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = env[i];
		i++;
	}
	return (new_env);
}

static int	add_new_variable(char ***env, char *name, char *value)
{
	char	**new_env;
	int		count;

	count = count_env_vars(*env);
	new_env = create_expanded_env(*env, count);
	if (!new_env)
		return (-1);
	new_env[count] = create_env_string(name, value);
	if (!new_env[count])
		return (free(new_env), -1);
	free(*env);
	*env = new_env;
	return (0);
}

int	env_set(char ***env, char *name, char *value)
{
	int	index;

	if (validate_env_params(env, name) == -1)
		return (-1);
	index = find_index(*env, name);
	if (index != -1)
		return (update_existing_var(*env, index, name, value));
	return (add_new_variable(env, name, value));
}
