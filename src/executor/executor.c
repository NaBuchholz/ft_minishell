/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:31 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/22 18:31:26 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	wait_for_child(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

static void	execute_in_child(char **argv, char **env)
{
	char	*exec_path;

	exec_path = find_executable(argv[0], env);
	if (!exec_path)
	{
		printf("-------NULL exec_path--------");
		command_error(argv[0], "command not found");
		free_argv(argv);
		exit(127);
	}
	execve(exec_path, argv, env);
	perror("minishell");
	free_argv(argv);
	free(exec_path);
	exit(127);
}

int	execute_external(t_cmd *cmd, char **env, int *exit_status)
{
	char	**argv;
	pid_t	pid;

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
		return (free_argv(argv), 1);
	}
	if (pid == 0)
		execute_in_child(argv, env);
	*exit_status = wait_for_child(pid);
	return (free_argv(argv), *exit_status);
}
