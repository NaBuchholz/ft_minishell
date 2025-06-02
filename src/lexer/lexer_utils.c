/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:59:48 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 14:39:49 by nbuchhol         ###   ########.fr       */
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

/**
 * @brief Check if character is a shell operator metacharacter.
 * @param c Character to check.
 * @return 1 if operator, 0 otherwise.
 */
int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Check if character is a metacharacter (operator or whitespace).
 * @param c Character to check.
 * @return 1 if metacharacter, 0 otherwise.
 */
int	is_metacharacter(char c)
{
	return (ft_isspace(c) || is_operator(c));
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

/**
 * @brief Calculate the length of a word token.
 * @param input Input string.
 * @param start Starting position in string.
 * @return Length of the word (number of characters).
 */
int	get_word_length(char *input, int start)
{
	int	len;

	len = 0;
	while (input[start + len] && !is_metacharacter(input[start + len]))
		len++;
	return (len);
}
