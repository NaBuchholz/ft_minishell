/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:05:29 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 19:20:52 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	is_builtin_command(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd_name, "exit", 5) == 0)
		return (1);
	return (0);
}

static int	execute_builtin_command(char **argv, t_shell *shell)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(argv, shell));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd(argv, shell));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(argv, shell));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(argv, shell));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(argv, shell->envp));
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (builtin_exit(argv, shell));
	return (1);
}

int	manage_builtin(t_cmd *cmd, t_shell *shell, int *exit_status)
{
	char	**argv;
	int		status;

	if (!cmd || !cmd->args || !cmd->args->value)
		return (0);
	if (!is_builtin_command(cmd->args->value))
		return (0);
	argv = cmd_to_argv(cmd);
	if (!argv)
	{
		*exit_status = 1;
		return (1);
	}
	status = execute_builtin_command(argv, shell);
	*exit_status = status;
	free_argv(argv);
	return (1);
}
