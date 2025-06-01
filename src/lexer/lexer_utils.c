/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:59:48 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 13:37:16 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Skip whitespace characters in input.
 * @param char* Pointer to current position in string.
 * @param int index of the current position in string.
 * @return Updated index position after whitespaces.
 */
int	skip_whitespace(char *input, int pos)
{
	while (input[pos] && ft_isspace(input[pos]))
		pos++;
	return (pos);
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Get token type based on string content.
 * @param char* Pointer to current position in string.
 * @param int index of the current position in string.
 * @return Corresponding token type enum.
 */
t_token_type	get_operator_type(char *input, int pos)
{
	if (input[pos] == '|')
		return (TOKEN_PIPE);
	if (input[pos] == '<')
		return (TOKEN_REDIR_IN);
	if (input[pos] == '>')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}
