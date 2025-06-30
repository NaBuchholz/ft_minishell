/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:14:43 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/22 17:29:59 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Checks if token should have $? expanded
 * @param token Token to check
 * @return 1 if should expand, 0 otherwise
 */
static int should_expand_token(t_token *token)
{
	if (!token || !token->value)
		return (0);
	if (token->type == TOKEN_SINGLE_QUOTE)
		return (0);
	return (contains_exit_status(token->value));
}

/**
 * @brief Expands $? in a single token
 * @param token Token to expand
 * @param status Exit status value
 * @return 0 on success, 1 on error
 */
int	expand_token_exit(t_token *token, int status)
{
	char	*expanded;

	if (!should_expand_token(token))
		return (0);
	expanded = expand_exit_status(token->value, status);
	if (!expanded)
		return (1);
	free(token->value);
	token->value = expanded;
	return (0);
}

/**
 * @brief Expands $? in all tokens
 * @param tokens Token list head
 * @param status Exit status value
 * @return 0 on success, 1 on error
 */
int	expand_tokens_exit(t_token *tokens, int status)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (expand_token_exit(current, status) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}

/**
 * @brief Updates shell exit status
 * @param shell Shell structure
 * @param status New exit status value
 */
void	update_exit_status(t_shell *shell, int status)
{
	if (shell)
		shell->exit_status = status;
}

/**
 * @brief Gets current exit status
 * @param shell Shell structure
 * @return Currente exit status or 0 if shell is NULL
 */
int	get_exit_status(t_shell *shell)
{
	if (!shell)
		return (0);
	return (shell->exit_status);
}
