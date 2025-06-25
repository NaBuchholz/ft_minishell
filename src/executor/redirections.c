/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:36:20 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 13:20:00 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	handle_out_redir(char *filename)
{
	int	file_fd;
	int	new_fd;

	file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	new_fd = dup2(file_fd, 1);
	if (new_fd == -1)
	{
		perror("minishell: dup2\n");
		close(file_fd);
		return (-1);
	}
	close(file_fd);
	return (0);
}

static int	handle_in_redir(char *filename)
{
	int	file_fd;
	int	new_fd;

	file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	new_fd = dup2(file_fd, 0);
	if (new_fd == -1)
	{
		perror("minishell: dup2\n");
		close(file_fd);
		return (-1);
	}
	close(file_fd);
	return (0);
}

static int	handle_in_redir(char *filename)
{
	int	file_fd;
	int	new_fd;

	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	new_fd = dup2(file_fd, 0);
	if (new_fd == -1)
	{
		perror("minishell: dup2\n");
		close(file_fd);
		return (-1);
	}
	close(file_fd);
	return (0);
}

static int	handle_redir_by_type(t_token_type type, char *target)
{
	if (type == TOKEN_REDIR_OUT)
		return (handle_out_redir(target));
	else if (type == TOKEN_REDIR_IN)
		return (handle_in_redir(target));
	else if (type == TOKEN_REDIR_APPEND)
		return (handle_append_redir(target));
//    else if (type == TOKEN_HEREDOC)
//       return (handle_heredoc_redir(target)); // Para quando implementar
	return (0);
}

int	apply_redirs(t_redir *redirections)
{
	t_redir	*current;

	if (!redirections)
		return (0);
	current = redirections;
	while (current)
	{
		if (handle_redir_by_type(current->type, current->target) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
