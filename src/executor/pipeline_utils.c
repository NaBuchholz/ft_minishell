/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 10:32:22 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/08 10:39:02 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	setup_child_pipes(int cmd_index, int cmd_count, int *pipes)
{
	if (cmd_index > 0)
	{
		if (dup2(pipes[(cmd_index - 1) * 2], STDIN_FILENO) == -1)
			return (perror("minishell: dup2"), 1);
	}
	if (cmd_index < cmd_count - 1)
	{
		if (dup2(pipes[cmd_index * 2 + 1], STDOUT_FILENO) == -1)
			return (perror("minishell: dup2"), 1);
	}
	return (0);
}

int	create_pipes(int **pipes, int pipe_count)
{
	int	i;

	*pipes = ft_calloc(pipe_count * 2, sizeof(int));
	if (!*pipes)
		return (1);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(&(*pipes)[i * 2]) == -1)
		{
			perror("minishell: pipe");
			free(*pipes);
			return (1);
		}
		printf("🔧 PIPE: Criado pipe[%d] = {%d, %d}\n",
			i, (*pipes)[i * 2], (*pipes)[i * 2 + 1]);
		i++;
	}
	return (0);
}

void	close_all_pipes(int *pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
	{
		close(pipes[i]);
		i++;
	}
}
