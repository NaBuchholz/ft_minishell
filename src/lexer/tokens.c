/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:33:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/05/31 19:16:39 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h";

/**
 * @brief create a token.
 * @param t_token_type enum to token types.
 * @param char* string value of token.
 * @return the token if created , otherwise NULL.
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value != NULL)
	{
		token->value = ft_strdup(value);
		if (!token->value)
		{
			free(token);
			return (NULL);
		}
	}
	return (token);
}

void	free_token(t_token *token)
{
	// Verificar se token não é NULL
	// Se token->value existe, liberar a string
	// Liberar o próprio token
}
