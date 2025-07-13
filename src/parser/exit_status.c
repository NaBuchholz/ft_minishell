/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:16:21 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/06 18:15:31 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Checks if $? pattern exists at position
 * @param str String to check
 * @param i Position to check
 * @return 1 if $? found, 0 otherwise
 */
int	is_exit_status(const char *str, int i)
{
	if (!str)
		return (0);
	if (str[i] != '$')
		return (0);
	if (str[i + 1] != '?')
		return (0);
	return (1);
}

/**
 * @brief Checks if string contains $? pattern
 * @param str String to check
 * @return 1 if contains $?, 0 otherwise
 */
int	contains_exit_status(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (is_exit_status(str, i))
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Extracts substring from string
 * @param str Source string
 * @param start Start position
 * @param len Length to extract
 * @return New allocated string or NULL on error
 */
char	*extract_segment(const char *str, int start, int len)
{
	if (!str || len <= 0)
		return (ft_strdup(""));
	return (ft_substr(str, start, len));
}

/**
 * @brief Main function to expand $? in string
 * @param str Input string
 * @param status Exit status value
 * @return New string with expansions or NULL on error
 */
char	*expand_exit_status(const char *str, int status)
{
	char	*result;

	if (!str)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	result = process_exit_status(result, str, status);
	return (result);
}
