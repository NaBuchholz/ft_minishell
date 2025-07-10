/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_heredoc_complete.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/10 13:21:42 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"
#include "heredoc.h"

/**
 * @brief Test basic heredoc creation and destruction
 * @return 0 on success, 1 on failure
 */
static int	test_heredoc_basic_creation(void)
{
	t_heredoc	*heredoc;

	printf("\n=== Test: heredoc basic creation ===\n");
	heredoc = create_heredoc("EOF", 0);
	if (!heredoc)
		return (printf("❌ FAIL: Heredoc creation failed\n"), 1);
	if (!heredoc->delimiter || ft_strncmp(heredoc->delimiter, "EOF", 3) != 0)
	{
		free_heredoc(heredoc);
		return (printf("❌ FAIL: Delimiter not set correctly\n"), 1);
	}
	if (heredoc->is_quoted != 0)
	{
		free_heredoc(heredoc);
		return (printf("❌ FAIL: Quote flag should be 0\n"), 1);
	}
	free_heredoc(heredoc);
	printf("✅ PASS: Basic heredoc creation successful\n");
	return (0);
}

/**
 * @brief Test quoted delimiter handling
 * @return 0 on success, 1 on failure
 */
static int	test_heredoc_quoted_delimiter(void)
{
	char	*normalized;

	printf("\n=== Test: heredoc quoted delimiter ===\n");
	normalized = normalize_delimiter("'EOF'");
	if (!normalized || ft_strncmp(normalized, "EOF", 3) != 0)
	{
		if (normalized)
			free(normalized);
		return (printf("❌ FAIL: Single quote normalization failed\n"), 1);
	}
	free(normalized);
	normalized = normalize_delimiter("\"END\"");
	if (!normalized || ft_strncmp(normalized, "END", 3) != 0)
	{
		if (normalized)
			free(normalized);
		return (printf("❌ FAIL: Double quote normalization failed\n"), 1);
	}
	free(normalized);
	printf("✅ PASS: Quoted delimiter handling successful\n");
	return (0);
}

/**
 * @brief Test delimiter validation
 * @return 0 on success, 1 on failure
 */
static int	test_heredoc_delimiter_validation(void)
{
	printf("\n=== Test: heredoc delimiter validation ===\n");
	if (!validate_heredoc_delimiter("EOF"))
		return (printf("❌ FAIL: Valid delimiter rejected\n"), 1);
	if (validate_heredoc_delimiter("E OF"))
		return (printf("❌ FAIL: Invalid delimiter accepted\n"), 1);
	if (validate_heredoc_delimiter(""))
		return (printf("❌ FAIL: Empty delimiter accepted\n"), 1);
	if (validate_heredoc_delimiter(NULL))
		return (printf("❌ FAIL: NULL delimiter accepted\n"), 1);
	printf("✅ PASS: Delimiter validation successful\n");
	return (0);
}

/**
 * @brief Test heredoc pipe creation
 * @return 0 on success, 1 on failure
 */
static int	test_heredoc_pipe_creation(void)
{
	t_heredoc	*heredoc;
	int			write_fd;

	printf("\n=== Test: heredoc pipe creation ===\n");
	heredoc = create_heredoc("EOF", 0);
	if (!heredoc)
		return (printf("❌ FAIL: Heredoc creation failed\n"), 1);
	write_fd = create_heredoc_pipe(heredoc);
	if (write_fd < 0)
	{
		free_heredoc(heredoc);
		return (printf("❌ FAIL: Pipe creation failed\n"), 1);
	}
	if (!validate_pipe_fd(heredoc->fd))
	{
		close(write_fd);
		free_heredoc(heredoc);
		return (printf("❌ FAIL: Read fd invalid\n"), 1);
	}
	close(write_fd);
	free_heredoc(heredoc);
	printf("✅ PASS: Pipe creation successful\n");
	return (0);
}

/**
 * @brief Test content expansion logic
 * @return 0 on success, 1 on failure
 */
static int	test_heredoc_expansion_logic(void)
{
	printf("\n=== Test: heredoc expansion logic ===\n");
	if (!should_expand_heredoc_content(0))
		return (printf("❌ FAIL: Should expand unquoted\n"), 1);
	if (should_expand_heredoc_content(1))
		return (printf("❌ FAIL: Should not expand quoted\n"), 1);
	printf("✅ PASS: Expansion logic correct\n");
	return (0);
}

/**
 * @brief Runs all heredoc tests
 * @return Number of failed tests
 */
int	run_complete_heredoc_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Complete Heredoc Tests ===\n");
	failures += test_heredoc_basic_creation();
	failures += test_heredoc_quoted_delimiter();
	failures
