/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:40:40 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/22 18:09:20 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Main function to apply exit status expansion on tokens
 * @param tokens Token list to process
 * @param shell Shell structure with exit status
 * @return 0 on success, 1 on error
 */
int	apply_exit_status(t_token *tokens, t_shell *shell)
{
	if (!tokens || !shell)
		return (0);
	return (expand_tokens_exit(tokens, shell->exit_status));
}

/**
 * @brief Processes raw input string with exit status
 * @param input Input string
 * @param shell Shell structure
 * @return Expanded string or NULL on error
 */
char	*process_input_with_exit(char *input, t_shell *shell)
{
	if (!input)
		return (ft_strdup(""));
	if (!shell)
		return (ft_strdup(input));
	if (!contains_exit_status(input))
		return (ft_strdup(input));
	return (expand_exit_status(input, shell->exit_status));
}

/**
 * @brief Checks if exit status needs to be updated based on return code
 * @param return_code Command return code
 * @return 1 if should update exit status, 0 otherwise
 */
static int	should_update_status(int return_code)
{
	if (return_code < 0)
		return (1);
	if (return_code > 255)
		return (1);
	if (return_code == 0)
		return (0);
	return (1);
}

/**
 * @brief Sets exit status after command execution
 * @param shell Shell structure
 * @param cmd_result Command execution result
 */
void	set_command_status(t_shell *shell, int cmd_result)
{
	if (!shell)
		return;
	if (should_update_status(cmd_result))
		update_exit_status(shell, cmd_result);
}

/**
 * @brief Updates and gets exit status in one operation
 * @param shell Shell structure
 * @param new_status New status to set (-1 to not update)
 * @return Current exit status after update
 */
int	update_and_get_status(t_shell *shell, int new_status)
{
	if (!shell)
		return (0);
	if (new_status >= 0)
		update_exit_status(shell, new_status);
	return (get_exit_status(shell));
}
