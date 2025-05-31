/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:25:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/05/31 20:03:13 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_create_token_with_value(void)
{
	t_token	*token;

	printf("\n=== Test: create_token with value ===\n");
	token = create_token(TOKEN_WORD, "hello");
	debug_token(token);
	if (!token)
	{
		printf("❌ FAIL: Token creation returned NULL\n");
		return (1);
	}
	if (token->type != TOKEN_WORD)
	{
		printf("❌ FAIL: Type should be TOKEN_WORD\n");
		free_token(token);
		return (1);
	}
	if (!token->value || ft_strncmp(token->value, "hello", 5) != 0)
	{
		printf("❌ FAIL: Value should be 'hello'\n");
		free_token(token);
		return (1);
	}
	printf("✅ PASS: Token with value\n");
	free_token(token);
	return (0);
}

static int	test_create_token_without_value(void)
{
	t_token	*token;

	printf("\n=== Test: create_token without value ===\n");
	token = create_token(TOKEN_PIPE, NULL);
	debug_token(token);
	if (!token)
	{
		printf("❌ FAIL: Token creation returned NULL\n");
		return (1);
	}
	if (token->type != TOKEN_PIPE)
	{
		printf("❌ FAIL: Type should be TOKEN_PIPE\n");
		free_token(token);
		return (1);
	}
	if (token->value != NULL)
	{
		printf("❌ FAIL: Value should be NULL\n");
		free_token(token);
		return (1);
	}
	printf("✅ PASS: Token without value\n");
	free_token(token);
	return (0);
}

static int	test_create_token_edge_cases(void)
{
	t_token	*token;

	printf("\n=== Test: create_token edge cases ===\n");
	token = create_token(TOKEN_WORD, "");
	debug_token(token);
	if (!token)
	{
		printf("❌ FAIL: Empty string token creation\n");
		return (1);
	}
	if (token->value && ft_strlen(token->value) != 0)
	{
		printf("❌ FAIL: Empty string not handled correctly\n");
		free_token(token);
		return (1);
	}
	printf("✅ PASS: Empty string handled\n");
	free_token(token);
	return (0);
}

int	run_token_creation_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Token Creation Tests ===\n");
	failures += test_create_token_with_value();
	failures += test_create_token_without_value();
	failures += test_create_token_edge_cases();
	printf("📊 Token Creation Tests: %d failures\n", failures);
	return (failures);
}
