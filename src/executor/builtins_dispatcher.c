/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:05:13 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 19:30:38 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_env_builtin(char **argv, t_shell *shell)
{
	return (builtin_env(argv, shell->envp));
}

static int	execute_export_builtin(char **argv, t_shell *shell)
{
	return (builtin_export(argv, shell));
}

static int	execute_unset_builtin(char **argv, t_shell *shell)
{
	return (builtin_unset(argv, shell));
}

static int	check_and_execute_builtin(char **argv, t_shell *shell)
{
	int	result;

	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (execute_env_builtin(argv, shell));
	else if (ft_strncmp(argv[0], "export", 7) == 0)
		return (execute_export_builtin(argv, shell));
	else if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (execute_unset_builtin(argv, shell));
	result = check_exit_builtin(argv, shell);
	if (result != -1)
		return (result);
	result = check_pwd_builtin(argv, shell);
	if (result != -1)
		return (result);
	return (-1);
}

/**
 * @brief Checks if a command is a built-in and execute it
 * @param cmd The command to be checked and executed
 * @param env The environment variables
 * @param exit_status Pointer to the exit status to be updated
 * @return Returns 1 if the command is a built-in (as was executed),
 * 0 otherwise
 */
int	dispatch_builtin(t_cmd *cmd, t_shell *shell, int *exit_status)
{
	char	**argv;
	int		result;

	argv = cmd_to_argv(cmd);
	if (!argv || !argv[0])
	{
		free_argv(argv);
		return (0);
	}
	result = check_and_execute_builtin(argv, shell);
	if (result != -1)
	{
		*exit_status = result;
		free_argv(argv);
		return (1);
	}
	free_argv(argv);
	return (0);
}
