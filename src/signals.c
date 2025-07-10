/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:44 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/10 12:10:58 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal_received = 0;

/**
 * @brief Signal handler for SIGINT (Ctrl+C)
 * @param sig Signal number
 */
static void	handle_sigint(int sig)
{
	g_signal_received = sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Setup signal handlers for interactive mode
 * @return 0 on success, 1 on error
 */
int	setup_interactive_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa_int, NULL) == -1)
	{
		perror("minishell: sigaction SIGINT");
		return (1);
	}
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) == -1)
	{
		perror("minishell: sigaction SIGQUIT");
		return (1);
	}
	return (0);
}

/**
 * @brief Setup signal handlers for child processes
 * @return 0 on success, 1 on error
 */
int	setup_child_signals(void)
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		perror("minishell: signal SIGINT");
		return (1);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		perror("minishell: signal SIGQUIT");
		return (1);
	}
	return (0);
}

/**
 * @brief Check and handle received signals
 * @param shell Shell structure to update exit status
 * @return 1 if SIGINT was received, 0 otherwise
 */
int	check_signals(t_shell *shell)
{
	if (g_signal_received == SIGINT)
	{
		shell->exit_status = 130;
		g_signal_received = 0;
		return (1);
	}
	return (0);
}
