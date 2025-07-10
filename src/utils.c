/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:20 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/09 21:51:46 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token)
		ft_putstr_fd(token, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
}

void	command_error(char *cmd, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}

/**
 * @brief Check if input is exit command.
 * @param input Input string to check.
 * @return 1 if exit command, 0 otherwise.
 */
int	is_exit_cmd(char *input)
{
	return (ft_strncmp(input, "exit", 4) == 0);
}


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