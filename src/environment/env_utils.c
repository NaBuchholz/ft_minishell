/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 14:00:15 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 14:00:31 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**cpy_env(char **envp)
{
	char	**copy;
	int		i;
	int		j;

	if (!envp)
		return (NULL);
	i = 0 ;
	while (envp[i])
		i++;
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
