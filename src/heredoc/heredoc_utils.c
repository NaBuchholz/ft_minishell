/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/10 13:06:55 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Creates a new heredoc structure
 * @param delimiter The delimiter string to match for end of input
 * @param is_quoted Whether the delimiter was quoted in the original input
 * @return Pointer to new heredoc structure or NULL on failure
 */
t_heredoc	*create_heredoc(char *delimiter, int is_quoted)
{
	t_heredoc	*heredoc;

	if (!delimiter)
		return (NULL);
	heredoc = ft_calloc(1, sizeof(t_heredoc));
	if (!heredoc)
		return (NULL);
	heredoc->delimiter = ft_strdup(delimiter);
	if (!heredoc->delimiter)
	{
		free(heredoc);
		return (NULL);
	}
	heredoc->content = NULL;
	heredoc->fd = -1;
	heredoc->is_quoted = is_quoted;
	return (heredoc);
}

/**
 * @brief Frees a heredoc structure and all its allocated memory
 * @param heredoc Pointer to heredoc structure to free
 */
void	free_heredoc(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	if (heredoc->delimiter)
		free(heredoc->delimiter);
	if (heredoc->content)
		free(heredoc->content);
	if (heredoc->fd >= 0)
		close(heredoc->fd);
	free(heredoc);
}

/**
 * @brief Validates if a delimiter string is valid for heredoc
 * @param delimiter The delimiter string to validate
 * @return 1 if valid, 0 if invalid
 */
int	validate_heredoc_delimiter(char *delimiter)
{
	int	i;

	if (!delimiter || !*delimiter)
		return (0);
	i = 0;
	while (delimiter[i])
	{
		if (ft_isspace(delimiter[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Normalizes a delimiter by removing quotes if present
 * @param raw_delimiter The raw delimiter string from input
 * @return Normalized delimiter string or NULL on failure
 */
char	*normalize_delimiter(char *raw_delimiter)
{
	int		len;
	char	quote_char;

	if (!raw_delimiter)
		return (NULL);
	len = ft_strlen(raw_delimiter);
	if (len < 2)
		return (ft_strdup(raw_delimiter));
	quote_char = raw_delimiter[0];
	if ((quote_char == '\'' || quote_char == '"')
		&& raw_delimiter[len - 1] == quote_char)
		return (ft_substr(raw_delimiter, 1, len - 2));
	return (ft_strdup(raw_delimiter));
}

/**
 * @brief Checks if a delimiter was originally quoted
 * @param delimiter The delimiter string to check
 * @return 1 if quoted, 0 if not quoted
 */
int	is_heredoc_delimiter_quoted(char *delimiter)
{
	int		len;
	char	first;
	char	last;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len < 2)
		return (0);
	first = delimiter[0];
	last = delimiter[len - 1];
	if ((first == '\'' && last == '\'') || (first == '"' && last == '"'))
		return (1);
	return (0);
}
