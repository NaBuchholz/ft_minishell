/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:01:01 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/01 22:20:25 by vinda-si         ###   ########.fr       */
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

int	env_unset(char ***env, char *name)
{
	int	status;
	int	var_index;

	status = 0;
	if (validate_env_params(env, name) == -1)
		return (status = 1);
	var_index = find_index(*env, name);
	if (var_index == -1)
		return (status);
	free((*env)[var_index]);
	while ((*env)[var_index + 1])
	{
		(*env)[var_index] = (*env)[var_index + 1];
		var_index++;
	}
	return (status);
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

	size = 0;
	while (shell->envp && shell->envp[size])
		size++;
	new_envp = ft_calloc(size + 2, sizeof(char *));
	if (!new_envp)
		return (1);
	size = -1;
	while (shell->envp && shell->envp[++size])
		new_envp[size] = shell->envp[size];
	new_envp[size] = ft_strdup(var);
	if (!new_envp[size])
	{
		free(new_envp);
		return (1);
	}
	if (shell->envp)
		free(shell->envp);
	shell->envp = new_envp;
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
