/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:47:45 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/14 13:50:23 by nbuchhol         ###   ########.fr       */
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
int	process_one_quote(const char *input, int *i, t_token **t_lst)
{
	char	*value;
	t_token	*new_token;

	(*i)++;
	if (extract_quoted_content(input, i, &value) != 0)
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
	add_token_to_list(t_lst, new_token);
	return (0);
}

/**
 * @brief Extracts text between double quotes.
 * @param input Input string being lexed.
 * @param i Pointer to current position; moces past closing quote.
 * @param out Receives malloc'ed substring (without quotes).
 * @return 0 on success, 1 on error.
 */
static int	extract_double_content(const char *input, int *index, char **out)
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
 * @param i Pointer to current position; updated after quote.
 * @param t_lst List head; new TOKEN_DOUBLE_QUOTE is appended.
 * @return 0 on success, 1 on error.
 */
int	process_two_quote(const char *input, int *i, t_token **t_lst)
{
	char	*value;
	t_token	*new;

	(*i)++;
	if (extract_double_content(input, i, &value) != 0)
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
	add_token_to_list(t_lst, new);
	return (0);
}

/**
 * @brief Create and add quote token into a list of tokens.
 * @param tokens** list of tokens.
 * @param input* String to be tokenized.
 * @param pos position.
 * @return new position of input, -1 in failure.
 */
int	handle_quotes(t_token **tokens, char *input, int pos)
{
	int	new_pos;

	new_pos = pos;
	if (input[pos] == '\'')
	{
		if (process_one_quote(input, &new_pos, tokens) != 0)
			return (-1);
	}
	else if (input[pos] == '"')
	{
		if (process_two_quote(input, &new_pos, tokens) != 0)
			return (-1);
	}
	return (new_pos);
}
