/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:30:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/08 11:07:53 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	execute_pipeline(t_cmd *cmd_list, char **env, int *exit_status)
{
	int		cmd_count;
	int		*pipes;
	pid_t	*pids;
	int		result;

	cmd_count = count_cmds(cmd_list);
	printf("🔗 PIPELINE: Executando %d comandos\n", cmd_count);
	if (cmd_count < 2)
		return (execute_external(cmd_list, env, exit_status));
	if (create_pipes(&pipes, cmd_count - 1) != 0)
		return (1);
	pids = ft_calloc(cmd_count, sizeof(pid_t));
	if (!pids)
		return (free(pipes), 1);
	result = fork_and_execute(cmd_list, pipes, pids, env);
	close_all_pipes(pipes, cmd_count - 1);
	if (result == 0)
		*exit_status = wait_all_processes(pids, cmd_count);
	free(pipes);
	free(pids);
	return (result);
}
