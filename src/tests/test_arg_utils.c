/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_arg_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:00:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/14 10:47:08 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test_add_arg_to_cmd_first(void)
{
	t_cmd	*cmd;
	t_arg	*arg;

	printf("\n=== Test: add first argument to command ===\n");
	cmd = create_cmd();
	arg = create_arg("ls", 0, 0);
	if (!cmd || !arg)
	{
		printf("❌ FAIL: Creation failed\n");
		return (1);
	}
	add_arg_to_cmd(cmd, arg);
	if (!cmd->args || cmd->args != arg)
	{
		printf("❌ FAIL: First argument not added correctly\n");
		free_cmd(cmd);
		return (1);
	}
	if (cmd->arg_count != 1)
	{
		printf("❌ FAIL: Argument count should be 1\n");
		free_cmd(cmd);
		return (1);
	}
	return (cleanup_and_return(NULL, "First argument added correctly", 0, cmd));
}

int	test_add_multiple_args_to_cmd(void)
{
	t_cmd	*cmd;
	t_arg	*arg1;
	t_arg	*arg2;

	printf("\n=== Test: add multiple arguments to command ===\n");
	cmd = create_cmd();
	arg1 = create_arg("ls", 0, 0);
	arg2 = create_arg("-la", 0, 0);
	if (!cmd || !arg1 || !arg2)
	{
		printf("❌ FAIL: Creation failed\n");
		return (1);
	}
	add_arg_to_cmd(cmd, arg1);
	add_arg_to_cmd(cmd, arg2);
	if (cmd->arg_count != 2)
	{
		printf("❌ FAIL: Argument count should be 2, got %d\n", cmd->arg_count);
		free_cmd(cmd);
		return (1);
	}
	printf("✅ PASS: Multiple arguments added correctly\n");
	free_cmd(cmd);
	return (0);
}

int	test_free_args_list(void)
{
	t_arg	*arg1;
	t_arg	*arg2;
	t_arg	*arg3;

	printf("\n=== Test: free arguments list ===\n");
	arg1 = create_arg("first", 0, 0);
	arg2 = create_arg("second", 1, 1);
	arg3 = create_arg("third", 1, 2);
	if (!arg1 || !arg2 || !arg3)
	{
		printf("❌ FAIL: Arguments creation failed\n");
		return (1);
	}
	arg1->next = arg2;
	arg2->next = arg3;
	printf("Created linked list with 3 arguments\n");
	free_args_lst(arg1);
	printf("✅ PASS: Arguments list freed without crash\n");
	return (0);
}

int	test_add_arg_null_cases(void)
{
	t_cmd	*cmd;
	t_arg	*arg;

	printf("\n=== Test: add argument NULL cases ===\n");
	cmd = create_cmd();
	arg = create_arg("test", 0, 0);
	if (!cmd || !arg)
	{
		printf("❌ FAIL: Creation failed\n");
		return (1);
	}
	add_arg_to_cmd(NULL, arg);
	add_arg_to_cmd(cmd, NULL);
	if (cmd->arg_count != 0)
	{
		printf("❌ FAIL: Count should remain 0 for NULL cases\n");
		free_arg(arg);
		free_cmd(cmd);
		return (1);
	}
	printf("✅ PASS: NULL cases handled correctly\n");
	free_arg(arg);
	free_cmd(cmd);
	return (0);
}

int	test_arg_list_traversal(void)
{
	t_cmd	*cmd;
	t_arg	*current;
	int		count;

	printf("\n=== Test: argument list traversal ===\n");
	cmd = create_cmd();
	add_arg_to_cmd(cmd, create_arg("cmd", 0, 0));
	add_arg_to_cmd(cmd, create_arg("arg1", 0, 0));
	add_arg_to_cmd(cmd, create_arg("arg2", 1, 2));
	count = 0;
	current = cmd->args;
	while (current)
	{
		count++;
		current = current->next;
	}
	if (count != 3 || cmd->arg_count != 3)
	{
		printf("❌ FAIL: Expected 3 args, traversed %d, count %d\n",
			count, cmd->arg_count);
		free_cmd(cmd);
		return (1);
	}
	return (cleanup_and_return(NULL, "List traversal successful", 0, cmd));
}
