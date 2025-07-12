/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:31 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/11 11:10:06 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	wait_all_processes(pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	exit_status;

	exit_status = 0;
	i = 0;
	while (i < cmd_count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
		{
			perror("minishell: waitpid");
			return (1);
		}
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGINT)
				{
					write(STDOUT_FILENO, "\n", 1);
					exit_status = 130;
				}
				else
					exit_status = 128 + WTERMSIG(status);
			}
			else
				exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}

/**
 * @brief Executes command in child process with heredoc support
 * @param env Environment variables
 * @param cmd Command to execute
 */
static void	execute_in_child(char **env, t_cmd *cmd)
{
	char	**argv;
	char	*exec_path;

	if (apply_redirs(cmd->redirections) == -1)
		exit(1);
	argv = cmd_to_argv(cmd);
	if (!argv)
		exit(127);
	printf("Comando: %s\n", argv[0]);
	exec_path = find_executable(argv[0], env);
	printf("Path encontrado: %s\n", exec_path ? exec_path : "NULL");
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

int	fork_single_command(t_cmd *cmd, int cmd_index, t_pipe_ctx *ctx, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("minishell: fork"), -1);
	if (pid == 0)
	{
		setup_child_signals();
		if (setup_child_pipes(cmd_index, ctx->cmd_count, ctx->pipes) != 0)
			exit(1);
		close_all_pipes(ctx->pipes, ctx->cmd_count - 1);
		execute_in_child(env, cmd);
	}
	return (pid);
}

int	fork_and_execute(t_cmd *cmd_list, int *pipes, pid_t *pids, char **env)
{
	t_cmd		*current;
	int			cmd_index;
	t_pipe_ctx	ctx;

	ctx.pipes = pipes;
	ctx.cmd_count = count_cmds(cmd_list);
	current = cmd_list;
	cmd_index = 0;
	while (current && cmd_index < ctx.cmd_count)
	{
		pids[cmd_index] = fork_single_command(current, cmd_index, &ctx, env);
		if (pids[cmd_index] == -1)
			return (1);
		current = current->next;
		cmd_index++;
	}
	return (0);
}

int	execute_external(t_cmd *cmd, char **env, int *exit_status)
{
	pid_t	pid;
	pid_t	pids[1];

	printf("🚀 EXECUTOR: Tentando executar '%s'\n",
		(cmd->args && cmd->args->value) ? cmd->args->value : "NULL");
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
	{
		setup_child_signals();
		execute_in_child(env, cmd);
	}
	setup_wait_signals();
	pids[0] = pid;
	*exit_status = wait_all_processes(pids, 1);
	setup_interactive_signals();
	return (*exit_status);
}
