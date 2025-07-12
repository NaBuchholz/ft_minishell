/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:18:58 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 17:20:48 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Block signals during critical operations
 * @return 0 on success, 1 on error
 */
int	block_signals(void)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1)
	{
		perror("minishell: sigprocmask block");
		return (1);
	}
	return (0);
}

/**
 * @brief Unblock signals after critical operations
 * @return 0 on success, 1 on error
 */
int	unblock_signals(void)
{
	sigset_t	mask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGQUIT);
	if (sigprocmask(SIG_UNBLOCK, &mask, NULL) == -1)
	{
		perror("minishell: sigprocmask unblock");
		return (1);
	}
	return (0);
}

/**
 * @brief Signal handler for SIGQUIT (Ctrl+\)
 * @param sig Signal number
 */
void	handle_sigquit(int sig)
{
	(void)sig;
	if (rl_line_buffer && rl_line_buffer[0] != '\0')
	{
		write(STDOUT_FILENO, "\nQuit (core dumped)\n", 20);
		exit(131);
	}
}
