/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:34:12 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 14:11:43 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Create and add operator token to the list.
 * @param tokens Double pointer to token list.
 * @param input Input string.
 * @param pos Current position in string.
 * @return Updated position after operator.
 */
int	handle_operator(t_token **tokens, char *input, int pos)
{
	t_token	*new_token;

	new_token = create_token(get_operator_type(input, pos), NULL);
	add_token_to_list(tokens, new_token);
	return (pos + 1);
}

/**
 * @brief Tokenize input string into a list of tokens.
 * @param input String to be tokenized.
 * @return Pointer to the first token of the list.
 */
t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		i = skip_whitespace(input, i);
		if (!input[i])
			break ;
		if (is_operator(input[i]))
			i = handle_operator(&tokens, input, i);
		else
			i++;
		//TODO: else com handle_word
	}
	return (tokens);
}
