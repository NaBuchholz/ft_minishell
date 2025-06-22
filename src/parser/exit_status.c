/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 00:16:21 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/21 01:00:05 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Checks if $? pattern exists at position
 * @param str String to check
 * @param i Position to check
 * @return 1 if $? found, 0 otherwise
 */
int is_exit_status(const char *str, int i)
{
	if (!str)
		return (0);
	return (str[i] == '$' && str[i + 1] == '?');
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
		if (is_exit_status(str, i));
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
 * @brief Appends s2 to s1, freeing s1
 * @param s1 First string
 * @param s2 Second string
 * @return New string or NULL on error
 */
char	*append_strings(char *s1, char *s2)
{
	char	*result;

	if (!s1)
	{
		if (!s2)
			return (ft_strdup(""));
		return (ft_strdup(s2));
	}
	if (!s2)
		return (s1);
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
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
	int		i;
	int		last;

	if (!str)
		return (NULL);
	init_expansion(&result, &i, &last);
	while (str[i])
	{
		if (is_exit_status(str, i))
		{
			if (process_segment(&result, str, last, i) != 0)
				return (NULL);
			if (process_exit_value(&result, status) != 0)
				return (NULL);
			i += 2;
			last = i;
		}
		else
			i++;
	}
	if (process_segment(&result, str, last, i) != 0)
		return (NULL);
	return (result);
}
