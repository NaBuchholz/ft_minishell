/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:16:12 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/16 21:34:08 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Main expansion function wrapper
 * @param input Input string with variables
 * @param envp Environment variables
 * @param status Exit status for $?
 * @return Expanded string or NULL on error
 */
char	*expand_variables(char const *input, char **envp, int status)
{
	t_exp_ctx	ctx;

	ctx.envp = envp;
	ctx.exit_status = status;
	return (process_expansion_with_ctx(input, &ctx));
}

/**
 * @brief Expands variables in a single token
 * @param token Token to expand
 * @param envp Environment variables
 * @param status Exit status
 * @return 0 on success, -1 on error
 */
int	expand_token(t_token *token, char **envp, int status)
{
	char	*expanded;

	if (!token || !token->value)
		return (0);
	if (token->type == TOKEN_SINGLE_QUOTE)
		return (0);
	expanded = expand_variables(token->value, envp, status);
	if (!expanded)
		return (1);
	free(token->value);
	token->value = expanded;
	return (0);
}

/**
 * @brief Expands variables in all tokens
 * @param tokens Token list
 * @param envp Environment variables
 * @param status Exit status
 * @return 0 on success, 1 on error
 */
int	expand_tokens(t_token *tokens, char **envp, int status)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (expand_token(current, envp, status) != 0)
			return (1);
		current = current->next;
	}
	return (0);
}
