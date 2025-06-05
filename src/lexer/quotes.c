/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:47:45 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/04 23:23:41 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int process_single_quote(const char *input, int *index, t_token **token_list)
{
	int		start_index;
	int		len;
	char	*value;
	t_token	*new_token;

	(*index)++;
	start_index = *index;
	while (input[*index] != '\0' && input[*index] != '\'')
		(*index)++;
	len = 0;
	if (input[*index] == '\'')
	{
		len = *index - start_index;
		value = (char *)malloc(sizeof(char) * (len + 1));
		
		if (!value)
			return (0);
		ft_strlcpy(value, &input[start_index], len + 1);
		(*index)++;

		new_token = (t_token *)malloc(sizeof(t_token));
		if (!new_token)
		{
			free(value);
			return (0);
		}
		new_token->type = TOKEN_SINGLE_QUOTE;
		new_token->value = value;
		new_token->next = NULL;
		(void)token_list;
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error: unclosed single quote\n", 2);
		return (0);
	}

}
