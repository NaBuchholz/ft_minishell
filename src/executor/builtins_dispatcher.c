/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_dispatcher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 23:05:13 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/02 21:47:34 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

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
	int		is_builtin;

	is_builtin = 0;
	argv = cmd_to_argv(cmd);
	if (!argv || !argv[0])
	{
		free_argv(argv);
		return (0);
	}
	if (ft_strncmp(argv[0], "env", 4) == 0)
	{
		*exit_status = builtin_env(argv, shell->envp);
		is_builtin = 1;
	}
	else if (ft_strncmp(argv[0], "export", 7) == 0)
	{
		*exit_status = builtin_export(argv, shell);
	}
	free_argv(argv);
	return (is_builtin);
}
