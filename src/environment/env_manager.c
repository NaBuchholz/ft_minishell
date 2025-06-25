/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:01:01 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 14:05:41 by nbuchhol         ###   ########.fr       */
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

// int	env_set(char ***env, char *name, char *value)
// {

// }

// int	env_unset(char ***env, char *name)
// {

// }
