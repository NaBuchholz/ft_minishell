/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:01:01 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 15:02:57 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_get(char **env, char *name)
{
	size_t	nl;
	int		j;

	nl = ft_strlen(name);
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], name, nl) == 0 && env[j][nl] == '=')
			return (ft_strdup(env[j] + nl + 1));
		j++;
	}
	return (ft_strdup(""));
}

static int	find_index(char **env, char *name)
{
	size_t	nl;
	int		j;

	nl = ft_strlen(name);
	j = 0;
	while (env[j])
	{
		if (ft_strncmp(env[j], name, nl) == 0 && env[j][nl] == '=')
			return (j);
		j++;
	}
	return (-1);
}

static char	*create_env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

int	env_set(char ***env, char *name, char *value)
{
	int		index;
	int		count;
	char	**new_env;
	int		i;

	if (!env || !*env || !name || !*name)
		return (-1);
	index = find_env_index(*env, name);
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = create_env_string(name, value);
		if (!(*env)[index])
			return (-1);
		return (0);
	}
	count = count_env_vars(*env);
	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return (-1);
	i = 0;
	while (i < count)
		new_env[i] = (*env)[i++];
	new_env[count] = create_env_string(name, value);
	if (!new_env[count])
		return (free(new_env), -1);
	free(*env);
	*env = new_env;
	return (0);
}

// int	env_unset(char ***env, char *name)
// {

// }
