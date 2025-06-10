/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser_syntax.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 09:03:02 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:13:28 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "test_utils.h"

/**
 * @brief Test syntax validation with valid inputs
 * @return 0 on success, 1 on failure
 */
int	test_valid_syntax(void)
{
	t_token	*tokens;
	int		result;

	printf("\n=== Test: valid syntax ===\n");
	tokens = tokenize_input("ls -la | grep test > output.txt");
	debug_token_list(tokens);
	result = validate_syntax(tokens);
	if (!result)
		return (cleanup_and_return(tokens, "Valid syntax failed", 1, NULL));
	return (cleanup_and_return(tokens, "Valid syntax passed", 0, NULL));
}

/**
 * @brief Test syntax validation with invalid pipe at start
 * @return 0 on success, 1 on failure
 */
int	test_invalid_pipe_start(void)
{
	t_token	*tokens;
	int		result;

	printf("\n=== Test: invalid pipe at start ===\n");
	tokens = tokenize_input("| ls -la");
	debug_token_list(tokens);
	result = validate_syntax(tokens);
	if (result)
		return (cleanup_and_return(tokens, "Should reject pipestart", 1, NULL));
	return (cleanup_and_return(tokens, "Pipe at start rejected", 0, NULL));
}

/**
 * @brief Test syntax validation with consecutive pipes
 * @return 0 on success, 1 on failure
 */
int	test_consecutive_pipes(void)
{
	t_token	*tokens;
	int		result;

	printf("\n=== Test: consecutive pipes ===\n");
	tokens = tokenize_input("ls || cat");
	debug_token_list(tokens);
	result = validate_syntax(tokens);
	if (result)
		return (cleanup_and_return(tokens, "Should reject || pipes", 1, NULL));
	return (cleanup_and_return(tokens, "Consecutive pipes rejected", 0, NULL));
}

/**
 * @brief Test redirection without target
 * @return 0 on success, 1 on failure
 */
int	test_invalid_redirection(void)
{
	t_token	*tokens;
	int		result;

	printf("\n=== Test: redirection without target ===\n");
	tokens = tokenize_input("ls >");
	debug_token_list(tokens);
	result = validate_syntax(tokens);
	if (result)
		return (cleanup_and_return(tokens, "Should reject no tgt", 1, NULL));
	return (cleanup_and_return(tokens, "Invalid redir rejected", 0, NULL));
}

