/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:08:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 17:50:17 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Reads a line safely for heredoc with signal checking
 * @param shell Pointer to shell structure for signal checking
 * @return Line read from input or NULL on EOF/interruption
 */
char	*read_heredoc_line_safe(t_shell *shell)
{
	char	*line;

	line = readline(HEREDOC_PROMPT);
	if (!line)
		return (NULL);
	if (check_heredoc_interrupted(shell))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/**
 * @brief Checks if a line matches the heredoc delimiter
 * @param line The line to check
 * @param delimiter The delimiter to match against
 * @return 1 if matches, 0 if not
 */
int	is_delimiter_match(char *line, char *delimiter)
{
	if (!line || !delimiter)
		return (0);
	return (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0
		&& ft_strlen(line) == ft_strlen(delimiter));
}

/**
 * @brief Joins multiple heredoc lines into single content string
 * @param lines Array of line strings
 * @param count Number of lines in array
 * @return Joined content string or NULL on failure
 */
char	*join_heredoc_lines(char **lines, int count)
{
	char	*content;
	char	*temp;
	int		i;

	if (!lines || count <= 0)
		return (ft_strdup(""));
	content = ft_strdup("");
	if (!content)
		return (NULL);
	i = 0;
	while (i < count)
	{
		temp = ft_strjoin(content, lines[i]);
		free(content);
		if (!temp)
			return (NULL);
		content = temp;
		temp = ft_strjoin(content, "\n");
		free(content);
		if (!temp)
			return (NULL);
		content = temp;
		i++;
	}
	return (content);
}

/**
 * @brief Frees array of heredoc lines
 * @param lines Array of line strings to free
 * @param count Number of lines in array
 */
static void	free_heredoc_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		if (lines[i])
			free(lines[i]);
		i++;
	}
	free(lines);
}

/**
 * @brief Main function to read heredoc content from input
 * @param ctx Heredoc context containing shell and heredoc data
 * @return 0 on success, 1 on failure or interruption
 */
int	read_heredoc_content(t_heredoc_ctx *ctx)
{
	char	**lines;
	int		count;

	if (!ctx || !ctx->heredoc)
		return (1);
	lines = ft_calloc(1024, sizeof(char *));
	if (!lines)
		return (1);
	count = read_lines_until_delimiter(ctx, lines);
	if (check_heredoc_interrupted(ctx->shell))
	{
		free_heredoc_lines(lines, count);
		return (1);
	}
	ctx->heredoc->content = join_heredoc_lines(lines, count);
	free_heredoc_lines(lines, count);
	if (ctx->heredoc->content)
		return (0);
	return (1);
}
