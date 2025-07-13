/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 11:02:01 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 12:07:50 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	print_pwd_error(void)
{
	ft_putstr_fd("minishell: pwd: ", 2);
	perror("");
}

static int	validate_pwd_args(char **argv)
{
	if (argv[1])
	{
		ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

static char	*get_current_directory(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		print_pwd_error();
		return (NULL);
	}
	return (pwd);
}

static int	print_directory(char *directory)
{
	if (!directory)
		return (1);
	ft_putstr_fd(directory, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}

/**
 * @brief Implementation of pwd builtin command
 * @param argv Command arguments
 * @param shell Shell structure
 * @return 0 on success, 1 on error
 */
int	builtin_pwd(char **argv, t_shell *shell)
{
	char	*current_dir;
	int		result;

	(void)shell;
	if (validate_pwd_args(argv) != 0)
		return (1);
	current_dir = get_current_directory();
	result = print_directory(current_dir);
	free(current_dir);
	return (result);
}
