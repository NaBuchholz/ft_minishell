/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:30:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/15 13:43:00 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test_simple_output_redirect(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: simple output redirect ===\n");
	tokens = tokenize_input("echo hello > file.txt");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd)
		return (cleanup_and_return(tokens, "Command parsing failed", 1, NULL));
	if (!cmd->redirections)
		return (cleanup_and_return(tokens, "No redirections found", 1, cmd));
	if (cmd->redirections->type != TOKEN_REDIR_OUT)
		return (cleanup_and_return(tokens, "Wrong redirect type", 1, cmd));
	if (!cmd->redirections->target
		|| ft_strncmp(cmd->redirections->target, "file.txt", 8) != 0)
		return (cleanup_and_return(tokens, "Wrong target file", 1, cmd));
	if (cmd->redirections->next != NULL)
		return (cleanup_and_return(tokens, "Should have 1 redirect", 1, cmd));
	return (cleanup_and_return(tokens, "Output redirect parsed", 0, cmd));
}

int	test_simple_input_redirect(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: simple input redirect ===\n");
	tokens = tokenize_input("cat < input.txt");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd)
		return (cleanup_and_return(tokens, "Command parsing failed", 1, NULL));
	if (!cmd->redirections)
		return (cleanup_and_return(tokens, "No redirections found", 1, cmd));
	if (cmd->redirections->type != TOKEN_REDIR_IN)
		return (cleanup_and_return(tokens, "Wrong redirect type", 1, cmd));
	if (!cmd->redirections->target
		|| ft_strncmp(cmd->redirections->target, "input.txt", 9) != 0)
		return (cleanup_and_return(tokens, "Wrong target file", 1, cmd));
	return (cleanup_and_return(tokens, "Input redirect parsed", 0, cmd));
}

int	test_append_redirect(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: append redirect ===\n");
	tokens = tokenize_input("echo hello >> file.txt");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd)
		return (cleanup_and_return(tokens, "Command parsing failed", 1, NULL));
	if (!cmd->redirections)
		return (cleanup_and_return(tokens, "No redirections found", 1, cmd));
	if (cmd->redirections->type != TOKEN_REDIR_APPEND)
		return (cleanup_and_return(tokens, "Wrong redirect type", 1, cmd));
	if (!cmd->redirections->target
		|| ft_strncmp(cmd->redirections->target, "file.txt", 8) != 0)
		return (cleanup_and_return(tokens, "Wrong target file", 1, cmd));
	return (cleanup_and_return(tokens, "Append redirect parsed", 0, cmd));
}

int	test_multiple_redirects(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;
	t_redir	*second;

	printf("\n=== Test: multiple redirects ===\n");
	tokens = tokenize_input("cmd < input.txt > output.txt");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (!cmd || !cmd->redirections)
		return (cleanup_and_return(tokens, "Command parsing failed", 1, cmd));
	if (cmd->redirections->type != TOKEN_REDIR_IN)
		return (cleanup_and_return(tokens, "First should be input", 1, cmd));
	second = cmd->redirections->next;
	if (!second || second->type != TOKEN_REDIR_OUT)
		return (cleanup_and_return(tokens, "Second should be output", 1, cmd));
	if (!cmd->redirections->target
		|| ft_strncmp(cmd->redirections->target, "input.txt", 9) != 0)
		return (cleanup_and_return(tokens, "Wrong input file", 1, cmd));
	if (!second->target
		|| ft_strncmp(second->target, "output.txt", 10) != 0)
		return (cleanup_and_return(tokens, "Wrong output file", 1, cmd));
	return (cleanup_and_return(tokens, "Multiple redirects parsed", 0, cmd));
}

int	test_redirect_without_target(void)
{
	t_token	*tokens;
	t_token	*current;
	t_cmd	*cmd;

	printf("\n=== Test: redirect without target ===\n");
	tokens = tokenize_input("echo hello >");
	current = tokens;
	cmd = parse_simple_cmd(&current);
	if (cmd && cmd->redirections)
		return (cleanup_and_return(tokens, "Should reject no target", 1, cmd));
	return (cleanup_and_return(tokens, "No target handled correctly", 0, cmd));
}
