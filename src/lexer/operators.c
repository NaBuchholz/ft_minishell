/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 20:41:28 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 20:48:41 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Get token type based on string content.
 * @param char* Pointer to current position in string.
 * @param int index of the current position in string.
 * @return Corresponding token type enum.
 */
t_token_type	get_operator_type(char *input, int pos)
{
	if (input[pos + 1] && input[pos] == '>' && input[pos + 1] == '>')
		return (TOKEN_REDIR_APPEND);
	if (input[pos + 1] && input[pos] == '<' && input[pos + 1] == '<')
		return (TOKEN_HEREDOC);
	if (input[pos] == '|')
		return (TOKEN_PIPE);
	if (input[pos] == '<')
		return (TOKEN_REDIR_IN);
	if (input[pos] == '>')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}
