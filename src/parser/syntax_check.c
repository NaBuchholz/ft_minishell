/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:24:55 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/21 13:08:24 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Check if there are operators at the beginning or end of token list.
 * @param tokens Pointer to the first token in the list.
 * @param input Input string.
 * @return pointer to the problematic token, NULL if valid.
 */
static t_token	*is_operator_at_edges(t_token *tokens)
{
	t_token	*last;

	if (!tokens)
		return (NULL);
	if (is_redirection(tokens->type) || tokens->type == TOKEN_PIPE)
		return (tokens);
	last = tokens;
	while (last->next)
		last = last->next;
	if (is_redirection(last->type) || last->type == TOKEN_PIPE)
		return (last);
	return (NULL);
}

/**
 * @brief Validate pipe syntax in token sequence.
 * @param tokens Pointer to the first token in the list.
 * @return Pointer to problematic token if invalid, NULL if valid.
 */
static t_token	*validate_pipe_syntax(t_token *tokens)
{
	t_token	*edge_error;

	if (!tokens)
		return (NULL);
	edge_error = is_operator_at_edges(tokens);
	if (edge_error)
		return (edge_error);
	while (tokens && tokens->next)
	{
		if (tokens->type == TOKEN_PIPE && tokens->next->type == TOKEN_PIPE)
			return (tokens->next);
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * @brief Validate all redirections in token sequence.
 * @param tokens Pointer to the first token in the list.
 * @return Pointer to wrong token, NULL if valid, (t_token *)-1 "newline" case
 */
static t_token	*validate_redirections(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	while (tokens)
	{
		if (is_redirection(tokens->type))
		{
			if (!tokens->next || tokens->next->type != TOKEN_WORD)
				return ((t_token *)-1);
			tokens = tokens->next;
		}
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * @brief Check for consecutive operators in token sequence
 * @param tokens Pointer to the first token in the list
 * @return 1 if consecutive operators found, 0 otherwise
 */
/**
 * @brief Check for consecutive operators in token sequence
 * @param tokens Pointer to the first token in the list
 * @return Pointer to problematic token if found, NULL otherwise
 */
static t_token	*has_consecutive_operators(t_token *tokens)
{
	t_token_type	current_type;
	t_token_type	next_type;

	if (!tokens)
		return (NULL);

	while (tokens && tokens->next)
	{
		current_type = tokens->type;
		next_type = tokens->next->type;
		if ((current_type == TOKEN_PIPE || is_redirection(current_type))
			&& (next_type == TOKEN_PIPE || is_redirection(next_type)))
			return (tokens->next);
		tokens = tokens->next;
	}
	return (NULL);
}

/**
 * @brief Validate complete syntax of token list
 * @param tokens Pointer to the first token in the list
 * @return 1 if syntax is valid, 0 if invalid
 */
t_token	*validate_syntax(t_token *tokens)
{
	t_token	*err_token;

	if (!tokens)
		return (NULL);
	err_token = validate_pipe_syntax(tokens);
	if (err_token)
		return (err_token);
	err_token = validate_redirections(tokens);
	if (err_token)
		return (err_token);
	err_token = has_consecutive_operators(tokens);
	if (err_token)
		return (err_token);
	return (NULL);
}
