/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:10:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/10 13:10:12 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Determines if heredoc content should be expanded
 * @param is_quoted Whether the delimiter was quoted
 * @return 1 if should expand, 0 if not
 */
int	should_expand_heredoc_content(int is_quoted)
{
	return (!is_quoted);
}

/**
 * @brief Expands variables in heredoc content
 * @param content The content string to expand
 * @param ctx Heredoc context containing environment and exit status
 * @return Expanded content string or NULL on failure
 */
char	*expand_heredoc_content(char *content, t_heredoc_ctx *ctx)
{
	char	*expanded;

	if (!content || !ctx)
		return (NULL);
	if (!should_expand_heredoc_content(ctx->heredoc->is_quoted))
		return (ft_strdup(content));
	expanded = expand_variables(content, ctx->envp, ctx->exit_status);
	if (!expanded)
		return (ft_strdup(content));
	return (expanded);
}

/**
 * @brief Processes heredoc content with expansion if needed
 * @param ctx Heredoc context
 * @return 0 on success, 1 on failure
 */
int	process_heredoc_expansion(t_heredoc_ctx *ctx)
{
	char	*expanded_content;

	if (!ctx || !ctx->heredoc || !ctx->heredoc->content)
		return (1);
	expanded_content = expand_heredoc_content(ctx->heredoc->content, ctx);
	if (!expanded_content)
		return (1);
	free(ctx->heredoc->content);
	ctx->heredoc->content = expanded_content;
	return (0);
}

/**
 * @brief Validates content size before processing
 * @param content Content string to validate
 * @return 1 if valid size, 0 if too large
 */
static int	validate_content_size(char *content)
{
	size_t	len;

	if (!content)
		return (1);
	len = ft_strlen(content);
	return (len <= MAX_HEREDOC_SIZE);
}

/**
 * @brief Main function to process heredoc with context
 * @param ctx Heredoc context containing all necessary data
 * @return 0 on success, 1 on failure
 */
int	process_heredoc_with_context(t_heredoc_ctx *ctx)
{
	if (!ctx || !ctx->shell || !ctx->heredoc)
		return (1);
	clear_heredoc_interrupted(ctx->shell);
	if (setup_heredoc_signals(ctx->shell) != 0)
		return (1);
	if (read_heredoc_content(ctx) != 0)
	{
		restore_interactive_signals(ctx->shell);
		return (1);
	}
	if (!validate_content_size(ctx->heredoc->content))
	{
		restore_interactive_signals(ctx->shell);
		return (1);
	}
	if (process_heredoc_expansion(ctx) != 0)
	{
		restore_interactive_signals(ctx->shell);
		return (1);
	}
	restore_interactive_signals(ctx->shell);
	return (0);
}
