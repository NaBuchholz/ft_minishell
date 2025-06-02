/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:59:48 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 20:49:59 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Skip whitespace characters in input.
 * @param input Pointer to current position in string.
 * @param pos Index of the current position in string.
 * @return Updated index position after whitespaces.
 */
int	skip_whitespace(char *input, int pos)
{
	while (input[pos] && ft_isspace(input[pos]))
		pos++;
	return (pos);
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
