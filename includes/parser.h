/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:38:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/11 20:58:40 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

/**
 * @brief Structure representing a redirection
 * @param type Type of redirection (>, <, >>, <<)
 * @param target Target file or delimiter for redirection
 * @param heredoc_fd File descriptor for heredoc (when applicable)
 * @param next Pointer to next redirection in the list
 */
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}t_redir;

/**
 * @brief Structure representing a command
 * @param args Array of command arguments (argv style)
 * @param arg_count Number of arguments in the command
 * @param redirections List of redirections for this command
 * @param has_heredoc Flag indicating if command has heredoc
 * @param next Pointer to next command in pipeline
 */
typedef struct s_cmd {
	char			**args;
	int				arg_count;
	t_redir			*redirections;
	int				has_heredoc;
	struct s_cmd	*next;
}t_cmd;

t_cmd	*create_cmd(int arg_count);
void	free_cmd(t_cmd *cmd);
int		is_operator_at_edges(t_token *tokens);
int		is_redirection(t_token_type type);
int		validate_pipe_syntax(t_token *tokens);
int		validate_redirections(t_token *tokens);
int		has_consecutive_operators(t_token *tokens);
int		count_cmds(t_cmd *cmd);
void	add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);
t_token	*find_next_pipe(t_token *start);
int		count_args(t_token *start);
int		validate_redir_target(t_token *target_token);
int		count_redirs_in_cmd(t_token *start, t_token *end);
t_cmd	*parse_simple_cmd(t_token **current);
t_redir	*create_redir(t_token_type type, char *target);
t_redir	*parse_redirs(t_token **current, t_token *end);
int		validate_syntax(t_token *tokens);

#endif
