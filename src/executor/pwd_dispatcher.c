/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_dispatcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:50:37 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 11:53:20 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

static int	execute_pwd_builtin(char **argv, t_shell *shell)
{
	return (builtin_pwd(argv, shell));
}

int	check_pwd_builtin(char **argv, t_shell *shell)
{
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (execute_pwd_builtin(argv, shell));
	return (-1);
}
