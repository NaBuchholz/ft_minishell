/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:00:15 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 18:39:00 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	validate_env_params(char ***env, char *name)
{
	if (!env || !*env || !name || !*name)
		return (-1);
	return (0);
}

char	**cpy_env(char **envp)
{
	char	**copy;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
	i = count_env_vars(envp);
	copy = ft_calloc(i + 1, sizeof (char *));
	if (!copy)
		return (NULL);
	j = 0;
	while (envp[j])
	{
		copy[j] = ft_strdup(envp[j]);
		if (!copy[j])
		{
			while (j > 0)
				free(copy[--j]);
			return (free(copy), NULL);
		}
		j++;
	}
	return (copy);
}

void	free_cpy_env(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

/**
 * @brief Finds the index of a environment variable by its name (key)
 * @param key The name of the variable to look for
 * @param env The environment to search in
 * @return The index if found, otherwise -1;
 */
int	get_env_index(char *key, char **env)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env && env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			if (env[i][key_len] == '=' || env[i][key_len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

char	**create_new_env_with_var(char **old_envp, char *var, int size, int i)
{
	char	**new_envp;

	new_envp = ft_calloc(size + 2, sizeof(char *));
	if (!new_envp)
		return (NULL);
	while (old_envp && old_envp[i])
	{
		new_envp[i] = ft_strdup(old_envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[--i]);
			return (free(new_envp), NULL);
		}
		i++;
	}
	new_envp[i] = ft_strdup(var);
	if (!new_envp[i])
	{
		while (i > 0)
			free(new_envp[--i]);
		return (free(new_envp), NULL);
	}
	return (new_envp);
}
