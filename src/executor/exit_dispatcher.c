/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:24:25 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 00:29:57 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_exit_builtin(char **argv, t_shell *shell)
{
	return (builtin_exit(argv, shell));
}

int	check_exit_builtin(char **argv, t_shell *shell)
{
	if (ft_strncmp(argv[0], "exit", 5) == 0)
		return (execute_exit_builtin(argv, shell));
	return (-1);
}
