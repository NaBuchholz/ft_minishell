/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:30:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/14 18:16:11 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	run_redirection_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Redirection Tests ===\n");
	failures += test_simple_output_redirect();
	failures += test_simple_input_redirect();
	failures += test_append_redirect();
	failures += test_multiple_redirects();
	failures += test_redirect_without_target();
	printf("📊 Redirection Tests: %d failures\n", failures);
	return (failures);
}

int	test(void)
{
	int	failures;

	failures = 0;
	failures += run_token_creation_tests();
	failures += run_lexer_tests();
	failures += run_memory_tests();
	failures += run_heredoc_tests();
	failures += run_parser_tests();
	failures += run_redirection_tests();
	return (failures);
}
