/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_argument.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:00:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/13 17:49:48 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test_create_arg_basic(void)
{
	t_arg	*arg;

	printf("\n=== Test: create basic argument ===\n");
	arg = create_arg("hello", 0, 0);
	if (!arg)
	{
		printf("❌ FAIL: Argument creation returned NULL\n");
		return (1);
	}
	if (!arg->value || ft_strncmp(arg->value, "hello", 5) != 0)
	{
		printf("❌ FAIL: Value should be 'hello'\n");
		free_arg(arg);
		return (1);
	}
	if (arg->is_quote != 0 || arg->quote_type != 0)
	{
		printf("❌ FAIL: Quote flags should be 0\n");
		free_arg(arg);
		return (1);
	}
	printf("✅ PASS: Basic argument created correctly\n");
	free_arg(arg);
	return (0);
}

int	test_create_quoted_arg(void)
{
	t_arg	*arg;

	printf("\n=== Test: create quoted argument ===\n");
	arg = create_arg("test string", 1, 2);
	if (!arg)
	{
		printf("❌ FAIL: Quoted argument creation returned NULL\n");
		return (1);
	}
	if (!arg->value || ft_strncmp(arg->value, "test string", 11) != 0)
	{
		printf("❌ FAIL: Value should be 'test string'\n");
		free_arg(arg);
		return (1);
	}
	if (arg->is_quote != 1 || arg->quote_type != 2)
	{
		printf("❌ FAIL: Quote flags incorrect\n");
		free_arg(arg);
		return (1);
	}
	printf("✅ PASS: Quoted argument created correctly\n");
	free_arg(arg);
	return (0);
}

int	test_create_arg_null_value(void)
{
	t_arg	*arg;

	printf("\n=== Test: create argument with NULL value ===\n");
	arg = create_arg(NULL, 0, 0);
	if (arg)
	{
		printf("❌ FAIL: Should return NULL for NULL value\n");
		free_arg(arg);
		return (1);
	}
	printf("✅ PASS: NULL value handled correctly\n");
	return (0);
}

int	test_create_arg_empty_string(void)
{
	t_arg	*arg;

	printf("\n=== Test: create argument with empty string ===\n");
	arg = create_arg("", 0, 0);
	if (!arg)
	{
		printf("❌ FAIL: Empty string argument creation failed\n");
		return (1);
	}
	if (!arg->value || ft_strlen(arg->value) != 0)
	{
		printf("❌ FAIL: Empty string not handled correctly\n");
		free_arg(arg);
		return (1);
	}
	printf("✅ PASS: Empty string argument created correctly\n");
	free_arg(arg);
	return (0);
}

int	test_arg_single_quote_type(void)
{
	t_arg	*arg;

	printf("\n=== Test: create single quote argument ===\n");
	arg = create_arg("literal text", 1, 1);
	if (!arg)
	{
		printf("❌ FAIL: Single quote argument creation failed\n");
		return (1);
	}
	if (arg->is_quote != 1 || arg->quote_type != 1)
	{
		printf("❌ FAIL: Single quote flags incorrect\n");
		free_arg(arg);
		return (1);
	}
	printf("✅ PASS: Single quote argument created correctly\n");
	free_arg(arg);
	return (0);
}
