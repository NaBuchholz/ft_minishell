/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modifiers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:05:46 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/13 18:39:45 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "environment.h"

int	count_env_vars(char **envp)
{
	int	size;

	size = 0;
	if (!envp)
		return (0);
	while (envp[size])
		size++;
	return (size);
}

static char	**recreate_env(char **old_envp, int size, int skip_index)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = ft_calloc(size, sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != skip_index)
		{
			new_envp[j] = ft_strdup(old_envp[i]);
			if (!new_envp[j])
			{
				while (j > 0)
					free(new_envp[--j]);
				return (free(new_envp), NULL);
			}
			j++;
		}
		i++;
	}
	return (new_envp);
}

/**
 * @brief Adds a new environment variable, reallocating the envp matrix
 * @param shell The shell struct containing the envp to be modified
 * @param var The full variable string
 * @return Returns 0 on sucess, 1 on allocation failure
 */
static int	add_new_env_var(t_shell *shell, char *var)
{
	int		size;
	char	**new_envp;
	char	**old_envp;

	size = 0;
	while (shell->envp && shell->envp[size])
		size++;
	new_envp = create_new_env_with_var(shell->envp, var, size, 0);
	if (!new_envp)
		return (1);
	old_envp = shell->envp;
	shell->envp = new_envp;
	if (old_envp)
		free_cpy_env(old_envp);
	return (0);
}

/**
 * @brief Sets or updates an environment variable
 * If the variable exists, it's updated, if not, it's created
 * @param shell The shell struct
 * @param var The variable string
 * @return Returns 0 on sucess, 1 on failure
 */
int	set_env_var(t_shell *shell, char *var)
{
	int		key_len;
	char	*key;
	int		index;

	key_len = ft_strchr(var, '=') - var;
	key = ft_substr(var, 0, key_len);
	if (!key)
		return (1);
	index = get_env_index(key, shell->envp);
	free(key);
	if (index != -1)
	{
		free(shell->envp[index]);
		shell->envp[index] = ft_strdup(var);
		if (!shell->envp[index])
			return (1);
	}
	else
	{
		if (add_new_env_var(shell, var) != 0)
			return (1);
	}
	return (0);
}

/**
 * @brief Removes an environment variable
 * If exists, it's removed, if not, nothing happens
 * @param shell The shell struct
 * @param key The key of the variable to remove
 * @return Returns 0 on success, 1 on failure
 */
int	unset_env_var(t_shell *shell, char *key)
{
	int		index;
	int		env_size;
	char	**new_envp;
	char	**old_envp;

	index = get_env_index(key, shell->envp);
	if (index == -1)
		return (0);
	env_size = count_env_vars(shell->envp);
	new_envp = recreate_env(shell->envp, env_size, index);
	if (!new_envp)
		return (1);
	old_envp = shell->envp;
	shell->envp = new_envp;
	free_cpy_env(old_envp);
	return (0);
}
