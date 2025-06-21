/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/21 17:05:36 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test_utils.h"
#include "executor.h"

char	*token_type_to_symbol(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("?");
}

/**
 * @brief Tokenize input and validate syntax.
 * @param input Input string to be tokenized and validated.
 * @return Valid token list on success, NULL on error or invalid syntax.
 */
static t_token	*validate_and_tokenize(char *input)
{
	t_token	*tokens;
	t_token	*err_token;

	tokens = tokenize_input(input);
	if (!tokens)
	{
		printf("❌ No tokens created\n");
		return (NULL);
	}
	err_token = validate_syntax(tokens);
	if (err_token)
	{
		if (err_token == (t_token *)-1)
			syntax_error(NULL);
		else
			syntax_error(token_type_to_symbol(err_token->type));
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}

/**
 * @brief Parse tokens into commands and execute them.
 * @param tokens Valid token list to be parsed and executed.
 * @return void
 */
static void	parse_and_execute(t_token *tokens, char **env, int *exit_status)
{
	t_cmd	*cmd;

	debug_token_list(tokens);
	cmd = parse_pipeline(tokens);
	if (cmd)
	{
		debug_cmd_list(cmd);
		execute_external(cmd, env, exit_status);
		free_cmd(cmd);
	}
}

/**
 * @brief Process the input and send to lexer analysis.
 * @param t_shell pointer to base struct to shell variables.
 * @param env pointer to the copy of enviroment variables.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	process_input(t_shell *shell, char **env)
{
	t_token	*tokens;

	if (ft_strncmp(shell->input, "exit", 4) == 0)
	{
		shell->should_exit = 1;
		return (1);
	}
	tokens = validate_and_tokenize(shell->input);
	if (!tokens)
		return (0);
	parse_and_execute(tokens, env, shell->exit_status);
	free_token_list(tokens);
	return (0);
}
