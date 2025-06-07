/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:47:45 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/06 21:55:13 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
