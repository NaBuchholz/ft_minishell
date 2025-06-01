/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:26:29 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 16:35:53 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_free_single_token(void)
{
	t_token	*token;

	printf("\n=== Test: free_single_token ===\n");
	token = create_token(TOKEN_WORD, "hello");
	if (!token)
	{
		printf("❌ FAIL: Token creation failed\n");
		return (1);
	}
	printf("Token created successfully\n");
	free_token(token);
	printf("✅ PASS: Token freed without crash\n");
	return (0);
}

static int	test_free_token_list(void)
{
	t_token	*tokens;
	t_token	*token1;
	t_token	*token2;

	printf("\n=== Test: free_token_list ===\n");
	tokens = NULL;
	token1 = create_token(TOKEN_WORD, "ls");
	token2 = create_token(TOKEN_PIPE, NULL);
	if (!token1 || !token2)
	{
		printf("❌ FAIL: Token creation failed\n");
		return (1);
	}
	add_token_to_list(&tokens, token1);
	add_token_to_list(&tokens, token2);
	printf("Token list created with 2 tokens\n");
	free_token_list(tokens);
	printf("✅ PASS: Token list freed without crash\n");
	return (0);
}

static int	test_memory_leaks(void)
{
	t_token	*tokens;
	int		i;

	printf("\n=== Test: memory_leaks (stress test) ===\n");
	i = 0;
	while (i < 100)
	{
		tokens = tokenize_input("|");
		free_token_list(tokens);
		i++;
	}
	printf("✅ PASS: 100 tokenize/free cycles completed\n");
	return (0);
}

int	run_memory_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Memory Tests ===\n");
	failures += test_free_single_token();
	failures += test_free_token_list();
	failures += test_memory_leaks();
	printf("📊 Memory Tests: %d failures\n", failures);
	return (failures);
}
