/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:00:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/28 20:07:02 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "environment.h"

int	test_env_get_existing_var(char **envp)
{
	char	**test_env;
	char	*result;

	printf("\n=== Test: env_get existing variable ===\n");
	test_env = cpy_env(envp);
	if (!test_env)
		return (printf("❌ FAIL: Environment copy failed\n"), 1);
	result = get_env_value("USER", test_env);
	if (!result)
	{
		free_cpy_env(test_env);
		return (printf("❌ FAIL: USER variable not found\n"), 1);
	}
	if (ft_strlen(result) == 0)
	{
		free_cpy_env(test_env);
		free(result);
		return (printf("❌ FAIL: USER variable is empty\n"), 1);
	}
	printf("✅ PASS: Found USER='%s'\n", result);
	free_cpy_env(test_env);
	free(result);
	return (0);
}

int	test_env_get_nonexistent_var(char **envp)
{
	char	**test_env;
	char	*result;

	printf("\n=== Test: env_get nonexistent variable ===\n");
	test_env = cpy_env(envp);
	if (!test_env)
		return (printf("❌ FAIL: Environment copy failed\n"), 1);
	result = get_env_value("DEFINITELY_NOT_EXISTS_VAR_12345", test_env);
	if (!result || ft_strlen(result) != 0)
	{
		free_cpy_env(test_env);
		free(result);
		return (printf("❌ FAIL: Should return empty string\n"), 1);
	}
	printf("✅ PASS: Nonexistent variable handled correctly\n");
	free_cpy_env(test_env);
	free(result);
	return (0);
}

int	test_find_index_basic(char **envp)
{
	char	**test_env;
	int		index;

	printf("\n=== Test: find_index basic functionality ===\n");
	test_env = cpy_env(envp);
	if (!test_env)
		return (printf("❌ FAIL: Environment copy failed\n"), 1);
	index = find_index(test_env, "USER");
	if (index < 0)
	{
		free_cpy_env(test_env);
		return (printf("❌ FAIL: USER should be found\n"), 1);
	}
	index = find_index(test_env, "DEFINITELY_NOT_EXISTS_VAR_12345");
	if (index != -1)
	{
		free_cpy_env(test_env);
		return (printf("❌ FAIL: Should return -1\n"), 1);
	}
	printf("✅ PASS: find_index working correctly\n");
	free_cpy_env(test_env);
	return (0);
}

int	validate_new_var(char **test_env)
{
	char	*result;

	result = get_env_value("MINISHELL_TEST_VAR", test_env);
	if (!result)
		return (printf("❌ FAIL: New variable not found\n"), 1);
	if (ft_strncmp(result, "test_value_123", 14) != 0)
	{
		printf("❌ FAIL: Wrong value, got '%s'\n", result);
		free(result);
		return (1);
	}
	free(result);
	return (0);
}

int	test_env_set_new_variable(char **envp)
{
	char	**test_env;

	printf("\n=== Test: env_set new variable ===\n");
	test_env = cpy_env(envp);
	if (!test_env)
		return (printf("❌ FAIL: Environment copy failed\n"), 1);
	if (env_set(&test_env, "MINISHELL_TEST_VAR", "test_value_123") != 0)
	{
		free_cpy_env(test_env);
		return (printf("❌ FAIL: env_set returned error\n"), 1);
	}
	if (validate_new_var(test_env) != 0)
	{
		free_cpy_env(test_env);
		return (1);
	}
	printf("✅ PASS: New variable added successfully\n");
	free_cpy_env(test_env);
	return (0);
}

