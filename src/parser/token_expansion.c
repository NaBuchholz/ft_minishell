/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 23:05:44 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/05 16:58:30 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Checks if expansion should occur based on token type
 * @param token_type Type of token being processed
 * @return 1 if expansion should occur, 0 otherwise
 */
static int	should_expand(t_token_type token_type)
{
	if (token_type == TOKEN_SINGLE_QUOTE)
		return (0);
	return (1);
}

/**
 * @brief Expands variables in a single token
 * @param token Token to process
 * @param envp Environment variables array
 * @param status Last command exit status
 * @return 0 on success, 1 on error
 */
int	expand_token(t_token *token, char **envp, int status)
{
	char	*expanded;

	if (!token || !token->value || !should_expand(token->type))
		return (0);
	expanded = expanded_variables(token->value, envp, status);
	if (!expanded)
		return (1);
	free(token->value);
	token->value = expanded;
	return (0);
}
