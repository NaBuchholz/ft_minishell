/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:01:01 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 18:26:18 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

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

int	find_index(char **env, char *name)
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

char	*create_env_string(char *name, char *value)
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

static char	**create_env_without_var(char **env, int skip_index, int i, int j)
{
	char	**new_env;
	int		count;

	count = count_env_vars(env);
	new_env = ft_calloc(count, sizeof(char *));
	if (!new_env)
		return (NULL);
	while (i < count)
	{
		if (i != skip_index)
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
			{
				while (j > 0)
					free(new_env[--j]);
				return (free(new_env), NULL);
			}
			j++;
		}
		i++;
	}
	return (new_env);
}

int	env_unset(char ***env, char *name)
{
	int		status;
	int		var_index;
	char	**new_env;
	char	**old_env;

	status = 0;
	if (validate_env_params(env, name) == -1)
		return (status = 1);
	var_index = find_index(*env, name);
	if (var_index == -1)
		return (status);
	new_env = create_env_without_var(*env, var_index, 0, 0);
	if (!new_env)
		return (1);
	old_env = *env;
	*env = new_env;
	free_cpy_env(old_env);
	return (status);
}


