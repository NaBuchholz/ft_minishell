/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_type_append.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 17:54:48 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:39:23 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test_append_operator_basic(void)
{
	t_token	*tokens;

	printf("\n=== Test: basic append operator ===\n");
	tokens = tokenize_input(">>");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_REDIR_APPEND)
		return (cleanup_and_return(tokens, "ExpecTOKEN_REDIR_APPEND", 1, NULL));
	if (tokens->next != NULL)
		return (cleanup_and_return(tokens, "Should have only 1token", 1, NULL));
	return (cleanup_and_return(tokens, "Append tokenized correctly", 0, NULL));
}

int	test_append_with_spaces(void)
{
	t_token	*tokens;

	printf("\n=== Test: append operator with spaces ===\n");
	tokens = tokenize_input("  >>  ");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_REDIR_APPEND)
		return (cleanup_and_return(tokens, "ExpecTOKEN_REDIR_APPEND", 1, NULL));
	if (tokens->next != NULL)
		return (cleanup_and_return(tokens, "Should have only 1token", 1, NULL));
	return (cleanup_and_return(tokens, "Append tokenized correctly", 0, NULL));
}

int	test_append_vs_redirect(void)
{
	t_token	*tokens;

	printf("\n=== Test: differentiate > and >> ===\n");
	tokens = tokenize_input("> >>");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_REDIR_OUT)
	{
		printf("❌ FAIL: First token should be TOKEN_REDIR_OUT\n");
		return (free_token_list(tokens), 1);
	}
	if (!tokens->next || tokens->next->type != TOKEN_REDIR_APPEND)
	{
		printf("❌ FAIL: Second token should be TOKEN_REDIR_APPEND\n");
		return (free_token_list(tokens), 1);
	}
	if (tokens->next->next != NULL)
	{
		printf("❌ FAIL: Should have only two tokens\n");
		return (free_token_list(tokens), 1);
	}
	printf("✅ PASS: > and >> differentiated correctly\n");
	free_token_list(tokens);
	return (0);
}

int	test_append_command(void)
{
	t_token	*tokens;
	t_token	*current;

	printf("\n=== Test: command with append ===\n");
	tokens = tokenize_input("echo hello >> file.txt");
	debug_token_list(tokens);
	current = tokens;
	if (!current || assert_token_equals(current, TOKEN_WORD, "echo"))
		return (cleanup_and_return(tokens, "1 token should be echo", 1, NULL));
	current = current->next;
	if (!current || assert_token_equals(current, TOKEN_WORD, "hello"))
		return (cleanup_and_return(tokens, "2token should be hello", 1, NULL));
	current = current->next;
	if (!current || current->type != TOKEN_REDIR_APPEND)
		return (cleanup_and_return(tokens, "2token should be REDIR", 1, NULL));
	current = current->next;
	if (!current || assert_token_equals(current, TOKEN_WORD, "file.txt"))
	{
		printf("❌ FAIL: Fourth token should be 'file.txt'\n");
		return (free_token_list(tokens), 1);
	}
	printf("✅ PASS: Command with append tokenized correctly\n");
	return (free_token_list(tokens), 0);
}

int	test_triple_redirect_edge_case(void)
{
	t_token	*tokens;

	printf("\n=== Test: triple redirect edge case ===\n");
	tokens = tokenize_input(">>>");
	debug_token_list(tokens);
	if (!tokens || tokens->type != TOKEN_REDIR_APPEND)
	{
		printf("❌ FAIL: First token should be TOKEN_REDIR_APPEND\n");
		return (free_token_list(tokens), 1);
	}
	if (!tokens->next || tokens->next->type != TOKEN_REDIR_OUT)
	{
		printf("❌ FAIL: Second token should be TOKEN_REDIR_OUT\n");
		return (free_token_list(tokens), 1);
	}
	if (tokens->next->next != NULL)
	{
		printf("❌ FAIL: Should have only two tokens\n");
		return (free_token_list(tokens), 1);
	}
	printf("✅ PASS: Triple redirect handled as >> + >\n");
	free_token_list(tokens);
	return (0);
}
