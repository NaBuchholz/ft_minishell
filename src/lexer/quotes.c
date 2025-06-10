/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:47:45 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/08 22:30:52 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Extracts text between single quotes.
 * @param input Input string being lexed.
 * @param index Pointer to current position; moves past closing quote.
 * @param extracted_value Receives malloc'ed sustring (without quotes).
 * @return 0 on success, 1 on error.
 */
static int	extract_quoted_content(const char *input,
		int *index, char **extracted_value)
{
	int	start_content_index;
	int	len;

	start_content_index = *index;
	while (input[*index] != '\0' && input[*index] != '\'')
		(*index)++;
	if (input[*index] == '\'')
	{
		len = *index - start_content_index;
		*extracted_value = (char *)malloc(sizeof(char) * (len + 1));
		if (!(*extracted_value))
			return (1);
		ft_strlcpy(*extracted_value, &input[start_content_index], len + 1);
		(*index)++;
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error: unclosed single quote\n", 2);
		*extracted_value = NULL;
		return (1);
	}
}
/**
 * @brief Tokenizes a single-quoted string.
 * @param input Full input line.
 * @param index Pointer to current position; updated after quote.
 * @param token_list List head; new TOKEN_SINGLE_QUOTE is appended.
 * @return 0 on success, 1 on error.
 */
int	ft_process_single_quote(const char *input, int *index, t_token **token_list)
{
	char	*value;
	t_token	*new_token;

	(*index)++;
	if (extract_quoted_content(input, index, &value) != 0)
		return (1);
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (1);
	}
	new_token->type = TOKEN_SINGLE_QUOTE;
	new_token->value = value;
	new_token->next = NULL;
	(void)token_list;
	return (0);
}
/**
 * @brief Extracts text between double quotes.
 * @param input Input string being lexed.
 * @param index Pointer to current position; moces past closing quote.
 * @param out Receives malloc'ed substring (without quotes).
 * @return 0 on success, 1 on error.
 */
static int	extract_double_content(const char * input, int *index, char **out)
{
	int	start;
	int	len;

	start = *index;
	while (input[*index] && input[*index] != '"')
		(*index)++;
	if (input[*index] != '"')
	{
		ft_putstr_fd("minishell: syntax error: unclosed double quote\n", 2);
		*out = NULL;
		return (1);
	}
	len = *index - start;
	*out = malloc(len + 1);
	if (!*out)
		return (1);
	ft_strlcpy(*out, &input[start], len + 1);
	(*index)++;
	return (0);
}

/**
 * @brief Tokenizes a doble-quoted string.
 * @param input Full input line.
 * @param index Pointer to current position; updated after quote.
 * @param token_list List head; new TOKEN_DOUBLE_QUOTE is appended.
 * @return 0 on success, 1 on error.
 */
int	ft_process_double_quote(const char *input, int *index, t_token **token_list)
{
	char	*value;
	t_token	*new;

	(*index)++;
	if (extract_double_content(input, index, &value) != 0)
		return (1);
	new = malloc(sizeof(t_token));
	if (!new)
	{
		free(value);
		return (1);
	}
	new->type = TOKEN_DOUBLE_QUOTE;
	new->value = value;
	new->next = NULL;
	(void)token_list;
	return (0);
}
