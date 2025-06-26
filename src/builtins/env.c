/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 20:11:29 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/25 21:44:09 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/**
 * @brief Execute the built-in 'env' command to print environment variables
 * @param argv The list of command arguments. The first argument must be "env"
 * @param envp The shell's environment variables
 * @return Retturns 0 on success, 1 if unexpected arguments are provided
 */
int	builtin_env(char **argv, char **envp)
{
	int	i;

	if (argv[1])
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		return (127);
	}

	i = 0;
	while (envp && envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
	return (0);
}
