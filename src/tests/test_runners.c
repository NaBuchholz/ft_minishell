/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:30:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/10 13:25:46 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "environment.h"

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
	failures += run_pipeline_tests();
	printf("📊 Redirection Tests: %d failures\n", failures);
	return (failures);
}

int	test(char **envp)
{
	int		failures;
	char	**env;

	failures = 0;
	failures += run_token_creation_tests();
	failures += run_lexer_tests();
	failures += run_memory_tests();
	failures += run_heredoc_tests();
	failures += run_parser_tests();
	failures += run_redirection_tests();
	failures += run_complete_heredoc_tests();
	env = cpy_env(envp);
	if (!env)
		return (failures++);
	failures += run_env_manager_tests(env);
	free_cpy_env(env);
	return (failures);
}
