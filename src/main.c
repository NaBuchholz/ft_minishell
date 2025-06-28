/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:52 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/28 19:56:29 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the readline loop.
 * @param t_shell pointer to base struct to shell variables.
 * @param envp pointer to enviroment variable.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	shell_loop(t_shell *shell, char **envp)
{
	char	**env;

	env = cpy_env(envp);
	if (!env)
		return (shell->should_exit = 1);
	printf("🔍 Minishell Debug Mode\n\n");
	while (!shell->should_exit)
	{
		shell->input = readline("minishell[DEBUG]> ");
		if (!shell->input)
		{
			printf("\n");
			shell->should_exit = 1;
			break ;
		}
		if (shell->input && *(shell->input))
		{
			add_history(shell->input);
			process_input(shell, env);
		}
		free(shell->input);
		shell->input = NULL;
	}
	free_cpy_env(env);
	return (shell->should_exit);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	if (argc == 2 && ft_strncmp(argv[1], "--test", 6) == 0)
		return (test(envp));
	ft_memset(&shell, 0, sizeof(t_shell));
	shell_loop(&shell, envp);
	return (0);
}
