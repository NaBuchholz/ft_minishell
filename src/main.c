/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:52 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 18:24:06 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialize shell environment and signals
 * @param shell Shell structure
 * @param envp Environment variables
 * @return Environment copy or NULL on failure
 */
static char	**init_shell_env(t_shell *shell, char **envp)
{
	char	**env;

	env = cpy_env(envp);
	if (!env)
	{
		shell->should_exit = 1;
		return (NULL);
	}
	shell->envp = env;
	rl_catch_signals = 0;
	if (setup_interactive_signals() != 0)
	{
		free_cpy_env(env);
		shell->envp = NULL;
		shell->should_exit = 1;
		return (NULL);
	}
	return (env);
}

/**
 * @brief Handle user input line
 * @param shell Shell structure
 * @param env Environment variables
 */
static void	handle_input_line(t_shell *shell)
{
	if (check_signals(shell))
		return ;
	if (shell->input && *(shell->input))
	{
		add_history(shell->input);
		process_input(shell);
	}
}

/**
 * @brief Main readline loop for interactive shell
 * @param shell Shell structure
 * @param env Environment variables
 */
static void	run_interactive_loop(t_shell *shell)
{
	while (!shell->should_exit)
	{
		shell->input = readline("minishell> ");
		if (!shell->input)
		{
			printf("\n");
			shell->should_exit = 1;
			break ;
		}
		handle_input_line(shell);
		free(shell->input);
		shell->input = NULL;
	}
}

/**
 * @brief Handles the readline loop.
 * @param shell pointer to base struct to shell variables.
 * @param envp pointer to environment variable.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	shell_loop(t_shell *shell, char **envp)
{
	char	**env;

	env = init_shell_env(shell, envp);
	if (!env)
		return (shell->should_exit);
	run_interactive_loop(shell);
	free_cpy_env(shell->envp);
	shell->envp = NULL;
	return (shell->should_exit);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	ft_memset(&shell, 0, sizeof(t_shell));
	shell_loop(&shell, envp);
	return (shell.exit_status);
}
