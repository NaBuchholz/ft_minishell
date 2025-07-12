/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:59:17 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 18:40:31 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	check_n_flags(const char *arg)
{
	int	i;

	if (!arg || arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (i > 1);
}

static void	print_args(char **args, int start_idx, int newline)
{
	int	i;

	i = start_idx;
	while(args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', 1);
}

static int	process_flags(char **args, int *start_idx)
{
	int	newline;
	int	i;

	newline = 1;
	i = 1;
	while (args[i] && check_n_flags(args[i]))
	{
		newline = 0;
		i++;
	}
	*start_idx = i;
	return (newline);
}

int	builtin_echo(char **args)
{
	int	start_idx;
	int	newline;

	if (!args || !args[0])
		return (1);
	newline = process_flags(args, &start_idx);
	if (args[start_idx])
		print_args(args, start_idx, newline);
	else if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}