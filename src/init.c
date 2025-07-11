/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/10 13:20:50 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#include "test_utils.h"
#include "executor.h"
#include "heredoc.h"

/**
 * @brief Processes heredocs for command pipeline before execution
 * @param cmd_list Pointer to command list
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
static int	process_heredocs_in_pipeline(t_cmd *cmd_list, t_shell *shell)
{
	t_heredoc_session	session;

	if (!cmd_list || !shell)
		return (0);
	if (start_heredoc_session(&session, shell) != 0)
		return (1);
	if (process_heredoc_session(&session, cmd_list) != 0)
	{
		end_heredoc_session(&session);
		return (1);
	}
	end_heredoc_session(&session);
	return (0);
}

/**
 * @brief Parse tokens into commands and execute them.
 * @param tokens Valid token list to be parsed and executed.
 * @param shell Pointer to shell structure
 * @return void
 */
static void	execute_commands(t_token *tokens, t_shell *shell)
{
	t_cmd	*cmd;

	debug_token_list(tokens);
	cmd = parse_pipeline(tokens);
	if (cmd)
	{
		debug_cmd_list(cmd);
		if (process_heredocs_in_pipeline(cmd, shell) != 0)
		{
			printf("❌ Heredoc processing failed\n");
			free_cmd_lst(cmd);
			return ;
		}
		if (cmd->next)
		{
			printf("🔗 EXECUTOR: Pipeline detectado\n");
			execute_pipeline(cmd, shell->envp, &shell->exit_status);
		}
		else
		{
			printf("🚀 EXECUTOR: Comando simples\n");
			execute_external(cmd, shell->envp, &shell->exit_status);
		}
		cleanup_heredoc_fds(cmd);
		free_cmd_lst(cmd);
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
	execute_commands(tokens, shell);
	free_token_list(tokens);
	return (0);
}
