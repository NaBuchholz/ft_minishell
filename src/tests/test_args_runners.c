/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_args_runners.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:00:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/13 17:51:11 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	run_argument_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Argument Tests ===\n");
	failures += test_create_arg_basic();
	failures += test_create_quoted_arg();
	failures += test_create_arg_null_value();
	failures += test_create_arg_empty_string();
	failures += test_arg_single_quote_type();
	printf("📊 Argument Tests: %d failures\n", failures);
	return (failures);
}

int	run_arg_utils_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Argument Utils Tests ===\n");
	failures += test_add_arg_to_cmd_first();
	failures += test_add_multiple_args_to_cmd();
	failures += test_free_args_list();
	failures += test_add_arg_null_cases();
	failures += test_arg_list_traversal();
	printf("📊 Argument Utils Tests: %d failures\n", failures);
	return (failures);
}
