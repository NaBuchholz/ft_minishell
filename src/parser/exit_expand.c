/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 18:25:40 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/05 16:59:16 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Process single $? occurrence
 * @param result Pointer to result string
 * @param str Input string
 * @param indices Array with [current, last] positions
 * @param status Exit status value
 * @return 0 on success, 1 on error
 */
static int	process_ocurrence(char **result, const char *str,
		int *indices, int status)
{
	if (append_segment(result, str, indices[1], indices[0])
		|| append_status(result, status))
		return (1);
	indices[0] += 2;
	indices[1] = indices[0];
	return (0);
}

/**
 * @brief Process exit pattern in string
 * @param result Result string
 * @param str Input string
 * @param status Exit status value
 * @return 0 on success, 1 on error
 */
static int	handle_exit_expand(char **result, int status)
{
	char	*status_str;
	char	*new_result;

	status_str = ft_itoa(status);
	if (!status_str)
		return (1);
	new_result = ft_strjoin(*result, status_str);
	free(status_str);
	free(*result);
	if (!new_result)
		return (1);
	*result = new_result;
	return (0);
}

/**
 * @brief Process full expansion of exit status
 * @param result Initial result string
 * @param str Input string
 * @param status Exit status value
 * @return Expanded string or NULL on error
 */
char	*process_exit_status(char *result, const char *str, int status)
{
	int	indices[2];

	indices[0] = 0;
	indices[1] = 0;
	while (str[indices[0]])
	{
		if (is_exit_status(str, indices[0]))
		{
			if (process_ocurrence(&result, str, indices, status))
			{
				free(result);
				return (NULL);
			}
		}
		else
			indices[0]++;
	}
	return (finalize_expansion(result, str, indices[1], indices[0]));
}

/**
 * @brief Finalizes expansion by adding remaining text
 * @param result Current result
 * @param str Input string
 * @param last Last processed position
 * @param i Current position
 * @return Completed string or NULL on error
 */
char	*finalize_expansion(char *result, const char *str, int last, int i)
{
	if (append_segment(&result, str, last, i))
	{
		free(result);
		return (NULL);
	}
	return (result);
}

/**
 * @brief Convenience function to start exit status expansion
 * @param str Input string
 * @param status Exit status value
 * @return Expanded string or NULL on error
 */
char	*start_exit_expansion(const char *str, int status)
{
	char	*result;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	return (process_exit_status(result, str, status));
}
