/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:45:46 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/30 18:52:59 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "parser.h"

int	execute_pipeline(t_cmd *cmd, char **env, int *exit_status)
{
	int		cmd_count;
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (!cmd || !env || !exit_status)
		return (1);
	cmd_count = count_cmds(cmd);
	if (cmd_count == 2)
	{
		if (pipe(pipefd) == -1)
		{
			perror("minishell: pipe");
			return (1);
		}
		printf("🔧 PIPE: criado com fd[0]=%d, fd[1]=%d\n", pipefd[0], pipefd[1]);
		pid1 = fork();
		if (pid1 == 0)
		{
		// Este código roda no FILHO1
        // configurar stdout → pipe
        // execve primeiro comando
		}
		pid2 = fork();
		if (pid2 == 0)
		{
		// Este código roda no FILHO2
        // configurar stdin ← pipe
        // execve segundo comando
		}
	}
	printf("🚀 PIPELINE: Executando 2 comandos\n");
	return (1);
}
