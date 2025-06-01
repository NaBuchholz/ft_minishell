/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:52 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 18:02:49 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles the readline loop.
 * @param t_shell pointer to base struct to shell variables.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	shell_loop(t_shell *shell)
{
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
			process_input(shell);
		}
		free(shell->input);
		shell->input = NULL;
	}
	return (shell->should_exit);
}

int	main(void)
{
	t_shell	shell;

	ft_memset(&shell, 0, sizeof(t_shell));
	shell_loop(&shell);
	return (0);
}
