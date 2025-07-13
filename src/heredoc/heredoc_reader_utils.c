/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:39:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 17:53:02 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Reads lines from input until delimiter is found
 * @param ctx Heredoc context containing shell and heredoc data
 * @param lines Array to store the lines
 * @return Number of lines read, or -1 on error
 */
int	read_lines_until_delimiter(t_heredoc_ctx *ctx, char **lines)
{
	char	*line;
	int		count;

	count = 0;
	while (count < 1023)
	{
		line = read_heredoc_line_safe(ctx->shell);
		if (!line || is_delimiter_match(line, ctx->heredoc->delimiter))
		{
			if (line)
				free(line);
			break ;
		}
		lines[count++] = line;
	}
	return (count);
}
