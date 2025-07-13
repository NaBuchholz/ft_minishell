/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:36:38 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/05 16:20:39 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	swap_if_needed(char **env, int current_index);

/**
 * @brief Compares two adjacent items in the env array and swaps them if need
 * @param env The environment array
 * @param current_index The index of the first item to compare
 */
static void	swap_if_needed(char **env, int current_index)
{
	char	*temp;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(env[current_index]);
	len2 = ft_strlen(env[current_index + 1]);
	if (len1 < len2)
		len1 = len2;
	if (ft_strncmp(env[current_index], env[current_index + 1], len1) > 0)
	{
		temp = env[current_index];
		env[current_index] = env[current_index + 1];
		env[current_index + 1] = temp;
	}
}

/**
 * @brief A simple bubble sort algorithm for the environment matrix
 */
void	bubble_sort_str_array(char **env, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			swap_if_needed(env, j);
			j++;
		}
		i++;
	}
}
