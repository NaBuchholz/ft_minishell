/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 00:05:04 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/13 10:24:56 by nbuchhol         ###   ########.fr       */
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

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static int	validate_exit_args(char **argv)
{
	if (!argv[1])
		return (0);
	if (!is_valid_number(argv[1]))
	{
		print_exit_error(argv[1]);
		return (2);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static int	parse_exit_status(char *arg)
{
	int	status;

	if (!arg)
		return (0);
	status = ft_atoi(arg);
	return (status % 256);
}
/**
 * @brief Implementation of exit builtin command
 * @param argv Command arguments
 * @param shell Shell structure
 * @return Exit status
 */

int	builtin_exit(char **argv, t_shell *shell)
{
	int	validation_result;
	int	exit_status;

	ft_putstr_fd("exit\n", 1);
	validation_result = validate_exit_args(argv);
	if (validation_result == 2)
	{
		shell->should_exit = 1;
		return (2);
	}
	if (validation_result == 1)
		return (1);
	exit_status = parse_exit_status(argv[1]);
	shell->should_exit = 1;
	shell->exit_status = exit_status;
	return (exit_status);
}
