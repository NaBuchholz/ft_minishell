/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:44:34 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:55:38 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	print_cmd_lst(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("No commands found!!");
		return ;
	}
	i = 0;
	while (cmd)
	{
		printf("----Debug command----\nCommand: %s\n", cmd->args[0]);
		if (cmd->arg_count > 1)
		{
			printf("Argumentos: ");
			i = 1;
			while (i < cmd->arg_count)
			{
				printf("%s", cmd->args[i]);
				if (i < cmd->arg_count - 1)
					printf(" ");
				i++;
			}
		}
		cmd = cmd->next;
	}
}


/**
 * @brief Test simple command parsing
 * @return 0 on success, 1 on failure
 */
static int	test_simple_command_parse(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: simple command parsing ===\n");
	tokens = tokenize_input("ls -la");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd)
	{
		cleanup_and_return(tokens, "Command parsing returned NULL", 1, NULL);
		return (1);
	}
	if (!cmd->args || !cmd->args[0] || ft_strncmp(cmd->args[0], "ls", 2) != 0)
	{
		cleanup_and_return(tokens, "First argument should be 'ls'", 1, cmd);
		return (1);
	}
	if (!cmd->args[1] || ft_strncmp(cmd->args[1], "-la", 3) != 0)
	{
		cleanup_and_return(tokens, "Second argument should be '-la'", 1, cmd);
		return (1);
	}
	cleanup_and_return(tokens, "Simple command parsed correctly", 0, cmd);
	return (0);
}

/**
 * @brief Test command with redirections
 * @return 0 on success, 1 on failure
 */
static int	test_command_with_redirections(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: command with redirections ===\n");
	tokens = tokenize_input("cat < input.txt > output.txt");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd)
	{
		cleanup_and_return(tokens, "Command parsing returned NULL", 1, NULL);
		return (1);
	}
	if (!cmd->args || !cmd->args[0] || ft_strncmp(cmd->args[0], "cat", 3) != 0)
	{
		cleanup_and_return(tokens, "Command should be 'cat'", 1, cmd);
		return (1);
	}
	if (!cmd->redirections)
	{
		cleanup_and_return(tokens, "Should have redirections", 1, NULL);
		return (1);
	}
	cleanup_and_return(tokens, "Command with redirections parsed", 0, NULL);
	return (0);
}

/**
 * @brief Run all parser tests
 * @return Number of failed tests
 */
int	run_parser_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Parser Tests ===\n");
	failures += test_valid_syntax();
	failures += test_invalid_pipe_start();
	failures += test_consecutive_pipes();
	failures += test_invalid_redirection();
	failures += test_simple_command_parse();
	failures += test_command_with_redirections();
	printf("📊 Parser Tests: %d failures\n", failures);
	return (failures);
}
