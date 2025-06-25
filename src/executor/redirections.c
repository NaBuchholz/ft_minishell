/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 20:36:20 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/24 21:43:24 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	apply_redirs(t_redir *redirections)
{
	t_redir	*current;

	if (!redirections)
		return (0);
	current = redirections;
	while (current)
	{
		if (current->type == TOKEN_REDIR_OUT)
		{
			if (handle_out_redir(current->target) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	handle_out_redir(char *filename)
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
