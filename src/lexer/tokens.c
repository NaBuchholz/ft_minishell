/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:33:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 13:44:24 by nbuchhol         ###   ########.fr       */
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

/**
 * @brief Free memory allocated for a single token.
 * @param token Pointer to token to be freed.
 * @return void.
 */
void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (*token->value)
		free(token->value);
	free(token);
}

/**
 * @brief Add a token to the end of the token list.
 * @param head Double pointer to the head of the token list.
 * @param new_token Pointer to the token to be added.
 * @return void
 */
void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*last;

	if (!new_token)
		return ;
	if (!(*head))
		*head = new_token;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new_token;
	}
}
