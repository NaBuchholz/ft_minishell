/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_dispatcher.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:59:54 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/11 20:06:33 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/**
 * @brief Dispatcher function for cd builtin
 * @param argv Command arguments
 * @param shell Shell structure
 * @return 0 on success, 1 on error
 */
int	execute_cd_builtin(char **argv, t_shell *shell)
{
	return (builtin_cd(argv, shell));
}

/**
 * @brief Checks if command is cd and execute it
 * @param cmd Command string
 * @param argv Command arguments
 * @param shell Shell structure
 * @return 1 if cd was executed, 0 if not cd command
 */
int	is_cd_command(char *cmd, char **argv, t_shell *shell)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (execute_cd_builtin(argv, shell));
	return (-1);
}