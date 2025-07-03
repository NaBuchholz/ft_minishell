/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 22:28:29 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/02 23:04:26 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

static int		is_valid_identifier(char *var);
static void		print_sorted_env(char **envp);
static void		process_export_args(char **argv, t_shell *shell, int *status);
static void		bubble_sort_env(char **env, int count);

/**
 * @brief Main function for the `export` builtin
 * Manages exporting variables or printing the sorted environment
 * @param argv The command arguments
 * @param shell The main shell struct
 * @return Returns 0 on success, 1 if invalid
 */
int	builtin_export(char **argv, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	if (!argv[1])
	{
		print_sorted_env(shell->envp);
		return (0);
	}
	else
		process_export_args(argv, shell, &exit_status);
	return (exit_status);
}

/**
 * @brief Iterates over the export arguments, validates and sets them
 */
static void	process_export_args(char **argv, t_shell *shell, int *status)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_valid_identifier(argv[i]))
		{
			ft_putstr_fd("minishell: export `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			*status = 1;
		}
		else if (ft_strchr(argv[i], '='))
		{
			if (set_env_var(shell, argv[i]) != 0)
				*status = 1;
		}
		i++;
	}
}

/**
 * @brief Validates if a string is a valid environment variable identifier
 */
static int	is_valid_identifier(char *var)
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Clones, sorts, and prints environment variables in `bash` format
 */
static void	print_sorted_env(char **envp)
{
	char	**env_copy;
	int		count;
	int		i;

	count = 0;
	while (envp && envp[count])
		count++;
	env_copy = cpy_env(envp);
	if (!env_copy)
		return ;
	bubble_sort_str_array(env_copy, count);
	i = -1;
	while (++i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_copy[i], 1);
	}
	free_cpy_env(env_copy);
}
