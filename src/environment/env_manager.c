/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:01:01 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/30 12:05:27 by nbuchhol         ###   ########.fr       */
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
