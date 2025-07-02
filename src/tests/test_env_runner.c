/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env_runner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 19:47:07 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/28 20:03:22 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "environment.h"

int	run_env_manager_tests(char **envp)
{
	int	failures;

	failures = 0;
	printf("=== Running Environment Manager Tests ===\n");
	failures += test_env_get_existing_var(envp);
	failures += test_env_get_nonexistent_var(envp);
	failures += test_find_index_basic(envp);
	failures += test_env_set_new_variable(envp);
	printf("📊 Environment Manager Tests: %d failures\n", failures);
	return (failures);
}
