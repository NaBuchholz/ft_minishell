/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/08 10:15:10 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_simple_pipe_parsing(void)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	printf("\n=== Test: simple pipe parsing ===\n");
	tokens = tokenize_input("ls | cat");
	if (!tokens)
		return (printf("❌ FAIL: Tokenization failed\n"), 1);
	cmd_list = parse_pipeline(tokens);
	if (!cmd_list)
		return (cleanup_and_return(tokens, "Pipeline parsing failed", 1, NULL));
	if (!cmd_list->next)
		return (cleanup_and_return(tokens, "Should have 2 commands", 1,
				cmd_list));
	if (ft_strncmp(cmd_list->args->value, "ls", 2) != 0)
		return (cleanup_and_return(tokens, "First cmd should be ls", 1,
				cmd_list));
	if (ft_strncmp(cmd_list->next->args->value, "cat", 3) != 0)
		return (cleanup_and_return(tokens, "Second cmd should be cat", 1,
				cmd_list));
	return (cleanup_and_return(tokens, "Simple pipe parsed correctly", 0,
			cmd_list));
}

static int	test_triple_pipe_parsing(void)
{
	t_token	*tokens;
	t_cmd	*cmd_list;
	t_cmd	*current;
	int		count;

	printf("\n=== Test: triple pipe parsing ===\n");
	tokens = tokenize_input("ls | grep .c | wc");
	cmd_list = parse_pipeline(tokens);
	if (!cmd_list)
		return (cleanup_and_return(tokens, "Pipeline parsing failed", 1, NULL));
	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count != 3)
		return (cleanup_and_return(tokens, "Should have 3 commands", 1,
				cmd_list));
	return (cleanup_and_return(tokens, "Triple pipe parsed correctly", 0,
			cmd_list));
}

int	run_pipeline_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Pipeline Tests ===\n");
	failures += test_simple_pipe_parsing();
	failures += test_triple_pipe_parsing();
	printf("📊 Pipeline Tests: %d failures\n", failures);
	return (failures);
}
