/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyx <nyx@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:31 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 10:32:46 by nyx              ###   ########.fr       */
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

static void	execute_in_child(char **env, t_cmd *cmd)
{
	char	**argv;
	char	*exec_path;

	if (apply_redirs(cmd->redirections) == -1)
		exit(1);
	argv = cmd_to_argv(cmd);
	if (!argv)
		exit(127);
	exec_path = find_executable(argv[0], env);
	if (!exec_path)
	{
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
	pid_t	pid;

	printf("🚀 EXECUTOR: Tentando executar '%s'\n", cmd->args->value);
	if (!cmd || !cmd->args)
	{
		printf("🚀 EXECUTOR: cmd sem args ou sem cmd\n");
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (1);
	}
	if (pid == 0)
		execute_in_child(env, cmd);
	*exit_status = wait_for_child(pid);
	return (*exit_status);
}
