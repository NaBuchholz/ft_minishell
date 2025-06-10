/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:24:55 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 14:34:37 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Check if there are operators at the beginning or end of token list.
 * @param tokens Pointer to the first token in the list.
 * @param input Input string.
 * @return 1 if operators found at edges, 0 otherwise.
 */
static int	is_operator_at_edges(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (0);
	if (is_redirection(tokens->type) || tokens->type == TOKEN_PIPE)
		return (1);
	last = tokens;
	while (last->next)
		last = last->next;
	if (is_redirection(last->type) || last->type == TOKEN_PIPE)
		return (1);
	return (0);
}

/**
 * @brief Validate pipe syntax in token sequence.
 * @param tokens Pointer to the first token in the list.
 * @param input Input string.
 * @return 1 if pipe syntax is valid, 0 if invalid.
 */
static int	validate_pipe_syntax(t_token *tokens)
{
	if (!tokens || is_operator_at_edges(tokens))
		return (0);
	while (tokens && tokens->next)
	{
		if (tokens->type == TOKEN_PIPE && tokens->next->type == TOKEN_PIPE)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

/**
 * @brief Validate all redirections in token sequence.
 * @param tokens Pointer to the first token in the list.
 * @return 1 if all redirections are valid, 0 if any is invalid.
 */
static int	validate_redirections(t_token *tokens)
{
	if (!tokens)
		return (1);
	while (tokens)
	{
		if (is_redirection(tokens->type))
		{
			if (!validate_redir_target(tokens->next))
				return (0);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (1);
}

/**
 * @brief Check for consecutive operators in token sequence
 * @param tokens Pointer to the first token in the list
 * @return 1 if consecutive operators found, 0 otherwise
 */
static int	has_consecutive_operators(t_token *tokens)
{
	t_token_type	current_type;
	t_token_type	next_type;

	if (!tokens)
		return (0);
	while (tokens && tokens->next)
	{
		current_type = tokens->type;
		next_type = tokens->next->type;
		if ((current_type == TOKEN_PIPE || is_redirection(current_type))
			&& (next_type == TOKEN_PIPE || is_redirection(next_type)))
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

/**
 * @brief Validate complete syntax of token list
 * @param tokens Pointer to the first token in the list
 * @return 1 if syntax is valid, 0 if invalid
 */
int	validate_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (!validate_pipe_syntax(tokens))
		return (0);
	if (!validate_redirections(tokens))
		return (0);
	if (has_consecutive_operators(tokens))
		return (0);
	return (1);
}

// 5. Mensagem de erro
//id	syntax_error(char *message, t_token *token);
// FAZER: Imprime mensagem de erro formatada
