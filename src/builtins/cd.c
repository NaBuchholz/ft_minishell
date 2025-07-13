/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:16:07 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/12 10:42:12 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static void	print_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

static char	*get_target_path(char **argv, char **envp)
{
	char	*home_path;

	if (!argv[1])
	{
		home_path = get_env_value("HOME", envp);
		if (!home_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (NULL);
		}
		return (ft_strdup(home_path));
	}
	return (ft_strdup(argv[1]));
}

static int	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (1);
	if (env_set(&shell->envp, "OLDPWD", old_pwd) != 0)
	{
		free(new_pwd);
		return (1);
	}
	if (env_set(&shell->envp, "PWD", new_pwd) != 0)
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	return (0);
}

static int	change_directory(char *path, t_shell *shell)
{
	char	*old_pwd;
	int		result;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (chdir(path) != 0)
	{
		print_cd_error(path);
		free(old_pwd);
		return (1);
	}
	result = update_pwd_vars(shell, old_pwd);
	free(old_pwd);
	return (result);
}

/**
 * @brief Implemation of cd builtin command
 * @param argv Command arguments
 * @param shell Shell structure
 * @return 0 on success, 1 on error
 */
int	builtin_cd(char **argv, t_shell *shell)
{
	char	*target_path;
	int		result;

	target_path = get_target_path(argv, shell->envp);
	if (!target_path)
		return (1);
	result = change_directory(target_path, shell);
	free(target_path);
	return (result);
}
