/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:16:31 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 13:23:32 by nbuchhol         ###   ########.fr       */
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
			exit_status = handle_exit_status(status);
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

	if (!cmd || !cmd->args)
		return (1);
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
