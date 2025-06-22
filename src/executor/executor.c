/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:31 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/21 12:22:10 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

extern char	**environ; //FIX colocar a env do vini no lugar dessa aqui.

int	wait_for_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	execute_in_child(char **argv)
{
	execve(argv[0], argv, environ);
	//TODO adicionar a env copy do vini mais tarde!
	perror("minishell");
	free_argv(argv);
	exit(127);
}

int	execute_external(t_cmd *cmd)
{
	char	**argv;
	pid_t	pid;
	int		status;

	printf("🚀 EXECUTOR: Tentando executar '%s'\n", cmd->args->value);
	if (!cmd || !cmd->args)
		return (1);
	argv = cmd_to_argv(cmd);
	if (!argv)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		free_argv(argv);
		return (1);
	}
	if (pid == 0)
		execute_in_child(argv);
	status = wait_for_child(pid);
	free_argv(argv);
	return (status);
}
