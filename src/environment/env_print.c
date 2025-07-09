/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 17:18:59 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/09 18:12:24 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	print_export_format(char *env_var)
{
	char	*equal_sing;

	equal_sing = ft_strchr(env_var, '=');
	if (equal_sing)
	{
		*equal_sing = '\0';
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(equal_sing + 1, 1);
		ft_putstr_fd("\"\n", 1);
		*equal_sing = '=';
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env_var, 1);
		ft_putstr_fd("\n", 1);
	}
}

static int	compare_env_vars(char *str1, char *str2)
{
	int	len1;
	int	len2;
	int	min_len;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	min_len = len1;
	if (len2 < len1)
		min_len = len2;
	return (ft_strncmp(str1, str2, min_len + 1));
}

static void	sort_env_array(char **env_copy, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (compare_env_vars(env_copy[j], env_copy[j + 1]) > 0)
			{
				temp = env_copy[j];
				env_copy[j] = env_copy[j + 1];
				env_copy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

static char	**copy_env_for_sort(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	count = count_env_vars(envp);
	env_copy = malloc(sizeof(char *) * (count + 1));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < count)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			free_cpy_env(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

/**
 * @brief Prints environment variables in sorted order
 * @param envp Environment variables array
 */
void	print_sorted_env(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	if (!envp)
		return ;
	env_copy = copy_env_for_sort(envp);
	if (!env_copy)
		return ;
	count = count_env_vars(env_copy);
	sort_env_array(env_copy, count);
	i = 0;
	while (env_copy[i])
	{
		print_export_format(env_copy[i]);
		i++;
	}
	free_cpy_env(env_copy);
}
