/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:28:29 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/09 17:18:21 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	is_valid_char(char c, int is_first)
{
	if (is_first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}

static int	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!is_valid_char(var[0], 1))
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!is_valid_char(var[i], 0))
			return (0);
		i++;
	}
	return (1);
}

static void	print_export_error(char *var)
{
	ft_putstr_fd("minishell: export `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	process_single_arg(char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
	{
		print_export_error(arg);
		return (1);
	}
	if (ft_strchr(arg, '='))
		return (set_env_var(shell, arg));
	return (0);
}

/**
 * @brief Function for the export builtin
 * @param argv The command arguments
 * @param shell The main shell struct
 * @return Returns 0 on sucess, 1 if invalid
 */
int	builtin_export(char **argv, t_shell *shell)
{
	int	i;
	int	exit_status;

	if (!argv[1])
	{
		print_sorted_env(shell->envp);
		return (0);
	}
	i = 1;
	exit_status = 0;
	while (argv[i])
	{
		if (process_single_arg(argv[i], shell) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
