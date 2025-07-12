/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:17:41 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 19:31:12 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "heredoc.h"

/**
 * @brief Handles heredoc redirection
 * @param redir Pointer to redirection structure
 * @return 0 on success, -1 on failure
 */
int	handle_heredoc_redir(t_redir *redir)
{
	int	new_fd;

	if (!redir || !redir->heredoc)
		return (-1);
	if (!validate_pipe_fd(redir->heredoc->fd))
		return (-1);
	new_fd = dup2(redir->heredoc->fd, STDIN_FILENO);
	if (new_fd == -1)
	{
		perror("minishell: dup2");
		return (-1);
	}
	close(redir->heredoc->fd);
	return (0);
}
