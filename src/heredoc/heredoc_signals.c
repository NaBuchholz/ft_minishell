/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 10:03:21 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/11 10:12:47 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "heredoc.h"

/**
 * @brief Signal handler for heredoc SIGINT
 * @param sig Signal number
 */
static void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	exit(130);
}

/**
 * @brief Setup signal handlers for heredoc mode
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on error
 */
int	setup_heredoc_signals(t_shell *shell)
{
	struct sigaction	sa_int;

	(void)shell;
	sa_int.sa_handler = heredoc_sigint_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell: sigaction SIGINT");
		return (1);
	}
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		perror("minishell: signal SIGQUIT");
		return (1);
	}
	return (0);
}

/**
 * @brief Restore interactive signals after heredoc
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on error
 */
int	restore_interactive_signals(t_shell *shell)
{
	(void)shell;
	return (setup_interactive_signals());
}

/**
 * @brief Check if heredoc was interrupted by signal
 * @param shell Pointer to shell structure
 * @return 1 if interrupted, 0 if not
 */
int	check_heredoc_interrupted(t_shell *shell)
{
	if (!shell)
		return (0);
	return (shell->heredoc_interrupted);
}

/**
 * @brief Set heredoc interrupted flag
 * @param shell Pointer to shell structure
 */
void	set_heredoc_interrupted(t_shell *shell)
{
	if (shell)
		shell->heredoc_interrupted = 1;
}

/**
 * @brief Clear heredoc interrupted flag
 * @param shell Pointer to shell structure
 */
void	clear_heredoc_interrupted(t_shell *shell)
{
	if (shell)
		shell->heredoc_interrupted = 0;
}
