/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 07:57:50 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:08:08 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_heredoc_operator_only(void)
{
	t_token	*tokens;

	printf("\n=== Test: heredoc operator only ===\n");
	tokens = tokenize_input("<<");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_HEREDOC)
	{
		printf("❌ FAIL: Expected TOKEN_HEREDOC\n");
		free_token_list(tokens);
		return (1);
	}
	if (tokens->next != NULL)
	{
		printf("❌ FAIL: Should have only one token\n");
		free_token_list(tokens);
		return (1);
	}
	printf("✅ PASS: Heredoc operator tokenized correctly\n");
	free_token_list(tokens);
	return (0);
}

static int	test_heredoc_with_delimiter(void)
{
	t_token	*tokens;
	t_token	*current;

	printf("\n=== Test: heredoc with delimiter ===\n");
	tokens = tokenize_input("<< EOF");
	debug_token_list(tokens);
	current = tokens;
	if (!current || current->type != TOKEN_HEREDOC)
		cleanup_and_return(tokens, "1 token should be TOKEN_HEREDOC", 1);
	current = current->next;
	if (!current || assert_token_equals(current, TOKEN_WORD, "EOF"))
		cleanup_and_return(tokens, "Second token should be 'EOF'", 1);
	if (current->next != NULL)
		cleanup_and_return(tokens, "Should have only two tokens", 1);
	printf("✅ PASS: Heredoc with delimiter tokenized correctly\n");
	free_token_list(tokens);
	return (0);
}

int	run_heredoc_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Heredoc Tests ===\n");
	failures += test_heredoc_operator_only();
	failures += test_heredoc_with_delimiter();
	printf("📊 Heredoc Tests: %d failures\n", failures);
	return (failures);
}
