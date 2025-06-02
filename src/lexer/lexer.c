/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:34:12 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 11:50:51 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "test_utils.h"

/**
 * @brief Create and add operator token to the list.
 * @param tokens Double pointer to token list.
 * @param input Input string.
 * @param pos Current position in string.
 * @return Updated position after operator.
 */
static int	handle_operator(t_token **tokens, char *input, int pos)
{
	t_token	*new_token;

	new_token = create_token(get_operator_type(input, pos), NULL);
	printf("🔍 Found operator: '%c'\n", input[pos]);
	printf("%s\n", token_type_to_string(new_token->type));
	add_token_to_list(tokens, new_token);
	return (pos + 1);
}

/**
 * @brief Create and add word token to the list.
 * @param tokens Double pointer to token list.
 * @param input Input string.
 * @param pos Current position in string.
 * @return Updated position after word, or -1 on error.
 */
static int	handle_word(t_token **tokens, char *input, int pos)
{
	int		start;
	int		len;
	char	*word_value;
	t_token	*new_token;

	start = pos;
	len = get_word_length(input, start);
	word_value = ft_substr(input, (unsigned int)start, (size_t)len);
	if (!word_value)
		return (-1);
	new_token = create_token(TOKEN_WORD, word_value);
	free(word_value);
	if (!new_token)
		return (-1);
	add_token_to_list(tokens, new_token);
	return (pos + len);
}

/**
 * @brief Tokenize input string into a list of tokens.
 * @param char* String to be tokenized.
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
			i = handle_word(&tokens, input, i);
		if (i == -1)
		{
			free_token_list(tokens);
			return (NULL);
		}
	}
	return (tokens);
}
