/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:14:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 16:59:09 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

char	*token_type_to_string(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	else
		return ("UNKNOWN");
}

void	debug_token(t_token *token)
{
	printf("-------DEBUG TOKEN-------\n");
	if (!token)
	{
		printf("No token found!!!!\n");
		return ;
	}
	printf("Token Type: %s \n", token_type_to_string(token->type));
	printf("Token Value: %s \n", token->value);
}

void	debug_token_list(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	printf("=== TOKEN LIST DEBUG ===\n");
	while (current)
	{
		printf("Token %d: %s", count, token_type_to_string(current->type));
		if (current->value)
			printf(" (value: %s)", current->value);
		printf("\n");
		current = current->next;
		count++;
	}
	printf("Total tokens: %d\n", count);
}

static int	check_token_value(t_token *token, char *expected)
{
	if (expected == NULL && token->value != NULL)
	{
		printf("❌ ASSERT FAIL: Expected NULL value, got '%s'\n", token->value);
		return (1);
	}
	if (expected != NULL && token->value == NULL)
	{
		printf("❌ ASSERT FAIL: Expected value '%s', got NULL\n", expected);
		return (1);
	}
	if (expected && token->value
		&& ft_strncmp(token->value, expected, ft_strlen(expected)) != 0)
	{
		printf("❌ ASSERT FAIL:Expec '%s', got '%s'\n", expected, token->value);
		return (1);
	}
	return (0);
}

/**
 * @brief Assert that a token matches expected type and value.
 * @param token Token to validate.
 * @param type Expected token type.
 * @param value Expected token value (can be NULL).
 * @return 0 if assertion passes, 1 if fails.
 */
int	assert_token_equals(t_token *token, t_token_type type, char *value)
{
	if (!token)
	{
		printf("❌ ASSERT FAIL: Token is NULL\n");
		return (1);
	}
	if (token->type != type)
	{
		printf("❌ ASSERT FAIL: Expected type %s, got %s\n",
			token_type_to_string(type), token_type_to_string(token->type));
		return (1);
	}
	return (check_token_value(token, value));
}
