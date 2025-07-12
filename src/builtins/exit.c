/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:05:04 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 00:21:49 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	get_exit_status(char *str)
{
	int	status;

	status = ft_atoi(str);
	if (status < 0)
		return (256 + (status % 256));
	return (status % 256);
}

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	exit_status;

	ft_putendl_fd("exit", 1);
	if (!argv[1])
	{
		shell->should_exit = 1;
		return (shell->exit_status);
	}
	if (!is_valid_number(argv[1]))
	{
		print_exit_error(argv[1]);
		shell->should_exit = 1;
		return (2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	exit_status = get_exit_status(argv[1]);
	shell->should_exit = 1;
	return (exit_status);
}
