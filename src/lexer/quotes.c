/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 22:47:45 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/04 22:16:25 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "minishell.h"

int process_single_quote(const char *input, int *index, t_token **token_list)
{
	int		start_index;
	char	*value;
	t_token	*new_token;

	(*index)++;
	start_index = *index;
	while (input[*index] != '\0' && input[*index] != '\'')
		(*index)++;
	if (input[*index] == '\'')
	{
		int
	}

}
