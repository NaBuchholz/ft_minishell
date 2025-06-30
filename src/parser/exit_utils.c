/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:47:06 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/22 18:24:55 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Initializes expansion variables
 * @param result Pointer to result string
 * @param i Pointer to current index
 * @param last Pointer to last position
 */
void	init_expansion(char **result, int *i, int *last)
{
	*result = ft_strdup("");
	*i = 0;
	*last = 0;
}

/**
 * @brief Appends segment to result
 * @param result Pointer to result string
 * @param str Input string
 * @param start Start position
 * @param end End position
 * @return 0 on sucess, 1 on error
 */
static int	append_segment(char **result, const char *str, int start, int end)
{
	char	*segment;
	char	*new_result;

	if (end <= start)
		return (0);
	segment = extract_segment(str, start, end - start);
	if (!segment)
		return (1);
	new_result = ft_strjoin(*result, segment);
	free(*result);
	free(segment);
	if (!new_result)
		return (1);
	*result = new_result;
	return (0);
}

/**
 * @brief Appends exit status value to result
 * @param result Pointer to result string
 * @param status Exit status value
 * @return 0 on success, 1 on error
 */
static int	append_status(char **result, int status)
{
	char	*status_str;
	char	*new_result;

	status_str = ft_itoa(status);
	if (!status_str)
		return (1);
	new_result = ft_strjoin(*result, status_str);
	free(*result);
	free(status_str);
	if (!new_result)
		return (1);
	*result = new_result;
	return (0);
}

/**
 * @brief Handles expansion of segments
 * @param result Pointer to result string
 * @param str Input string
 * @param positions Array with [current, last] positions
 * @return 0 on success, 1 on error
 */
int	handle_segment(char **result, const char *str, int *positions)
{
	if (positions[0] <= positions[1])
		return (0);
	return (append_segment(result, str, positions[1], positions[0]));
}
