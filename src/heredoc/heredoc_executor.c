/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/10 13:12:12 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Creates heredoc context from shell and redirection
 * @param ctx Pointer to context structure to fill
 * @param redir Pointer to redirection structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
static int	create_heredoc_context(t_heredoc_ctx *ctx, t_redir *redir,
		t_shell *shell)
{
	if (!ctx || !redir || !shell)
		return (1);
	ctx->shell = shell;
	ctx->heredoc = redir->heredoc;
	ctx->envp = shell->envp;
	ctx->exit_status = shell->exit_status;
	return (0);
}

/**
 * @brief Processes a single heredoc redirection
 * @param redir Pointer to redirection structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
int	process_single_heredoc(t_redir *redir, t_shell *shell)
{
	t_heredoc_ctx	ctx;

	if (!redir || !shell || redir->type != TOKEN_HEREDOC)
		return (1);
	if (!redir->heredoc)
	{
		if (prepare_heredoc_data(redir, shell) != 0)
			return (1);
	}
	if (create_heredoc_context(&ctx, redir, shell) != 0)
		return (1);
	if (process_heredoc_with_context(&ctx) != 0)
		return (1);
	if (setup_heredoc_pipe_system(redir->heredoc) != 0)
		return (1);
	redir->heredoc_fd = redir->heredoc->fd;
	return (0);
}

/**
 * @brief Executes all heredocs for a command
 * @param cmd Pointer to command structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
int	execute_heredocs_for_cmd(t_cmd *cmd, t_shell *shell)
{
	t_redir	*current;

	if (!cmd || !shell)
		return (1);
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			if (process_single_heredoc(current, shell) != 0)
				return (1);
		}
		current = current->next;
	}
	return (0);
}

/**
 * @brief Cleans up heredoc file descriptors for a command
 * @param cmd Pointer to command structure
 */
void	cleanup_heredoc_fds(t_cmd *cmd)
{
	t_redir	*current;

	if (!cmd)
		return ;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC && current->heredoc)
			close_heredoc_pipe(current->heredoc);
		current = current->next;
	}
}

/**
 * @brief Validates heredoc setup for command
 * @param cmd Pointer to command structure
 * @return 1 if valid, 0 if invalid
 */
int	validate_heredoc_setup(t_cmd *cmd)
{
	t_redir	*current;
	int		heredoc_count;

	if (!cmd)
		return (0);
	heredoc_count = 0;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
		{
			heredoc_count++;
			if (!current->target)
				return (0);
		}
		current = current->next;
	}
	return (heredoc_count > 0);
}
