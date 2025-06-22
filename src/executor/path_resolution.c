/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:54:50 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/22 12:28:41 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	has_slash(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (1);
	return (0);
}

int	is_executable(char *path)
{
	struct stat	file_stat;

	if (!path)
		return (0);
	if (access(path, F_OK | X_OK) != 0)
		return (0);
	if (stat(path, &file_stat) != 0)
		return (0);
	return (S_ISREG(file_stat.st_mode));
}

static char	*find_path_in_env(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*build_full_path(char *dir, char *cmd_name)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd_name);
	free(temp);
	return (full_path);
}

char	*find_executable(char *cmd_name, char **env)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd_name || !env)
		return (NULL);
	if (has_slash(cmd_name))
	{
		if (is_executable(cmd_name))
			return (ft_strdup(cmd_name));
		return (NULL);
	}
	paths = ft_split(find_path_in_env(env), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd_name);
		if (full_path && is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
