/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 17:08:44 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/06 19:04:48 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int	is_valid_identifier_unset(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	builtin_unset(char **argv, t_shell *shell)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (argv[i])
	{
		if (!is_valid_identifier_unset(argv[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_status = 1;
		}
		else
		{
			if (unset_env_var(shell, argv[i]) != 0)
				exit_status = 1;
		}
		i++;
	}
	return (exit_status);
}
