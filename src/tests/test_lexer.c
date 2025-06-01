/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:35:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 16:53:05 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_single_pipe(void)
{
	t_token	*tokens;

	printf("\n=== Test: single pipe operator ===\n");
	tokens = tokenize_input("|");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_PIPE)
	{
		printf("❌ FAIL: Expected TOKEN_PIPE\n");
		free_token_list(tokens);
		return (1);
	}
	printf("✅ PASS: Single pipe tokenized correctly\n");
	free_token_list(tokens);
	return (0);
}

static int	test_redirect_operators(void)
{
	t_token	*tokens;

	printf("\n=== Test: redirect operators ===\n");
	tokens = tokenize_input("< >");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_REDIR_IN)
	{
		printf("❌ FAIL: Expected TOKEN_REDIR_IN first\n");
		free_token_list(tokens);
		return (1);
	}
	if (!tokens->next || tokens->next->type != TOKEN_REDIR_OUT)
	{
		printf("❌ FAIL: Expected TOKEN_REDIR_OUT second\n");
		free_token_list(tokens);
		return (1);
	}
	printf("✅ PASS: Redirect operators tokenized correctly\n");
	free_token_list(tokens);
	return (0);
}

static int	test_operators_with_spaces(void)
{
	t_token	*tokens;

	printf("\n=== Test: operators with spaces ===\n");
	tokens = tokenize_input("  |  ");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_PIPE)
	{
		printf("❌ FAIL: Spaces not handled correctly\n");
		free_token_list(tokens);
		return (1);
	}
	if (tokens->next != NULL)
	{
		printf("❌ FAIL: Should have only one token\n");
		free_token_list(tokens);
		return (1);
	}
	printf("✅ PASS: Spaces handled correctly\n");
	free_token_list(tokens);
	return (0);
}

int	run_lexer_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Lexer Tests ===\n");
	failures += test_single_pipe();
	failures += test_redirect_operators();
	failures += test_operators_with_spaces();
	printf("📊 Lexer Tests: %d failures\n", failures);
	return (failures);
}
