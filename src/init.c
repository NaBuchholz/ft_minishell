/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 20:00:52 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "test_utils.h"
#include "executor.h"

/**
 * @brief Parse tokens into commands and execute them.
 * @param tokens Valid token list to be parsed and executed.
 * @return void
 */
static void	execute_commands(t_token *tokens, char **env, int *exit_status)
{
	t_cmd	*cmd;
	t_cmd	*last_cmd;

	debug_token_list(tokens);
	cmd = parse_pipeline(tokens);
	if (cmd)
	{
		last_cmd = cmd;
		while (last_cmd && last_cmd->next)
			last_cmd = last_cmd->next;
		debug_cmd_list(cmd);
		execute_external(cmd, env, exit_status);
		free_cmd(cmd);
	}
}

/**
 * @brief Process user input through lexer, parser and executor.
 * @param shell Pointer to shell structure.
 * @param env Environment variables.
 * @return 1 if shell should exit, 0 otherwise.
 */
int	process_input(t_shell *shell, char **env)
{
	t_token	*tokens;
	t_token	*err_token;

	if (is_exit_cmd(shell->input))
	{
		shell->should_exit = 1;
		return (1);
	}
	tokens = tokenize_input(shell->input);
	if (!tokens)
		return (0);
	if (expand_token_variables(tokens, env, shell->exit_status))
	{
		free_token_list(tokens);
		return (0);
	}
	err_token = validate_syntax(tokens);
	if (err_token)
	{
		handle_syntax_error(err_token, tokens);
		return (0);
	}
	execute_commands(tokens, env, &shell->exit_status);
	free_token_list(tokens);
	return (0);
}
