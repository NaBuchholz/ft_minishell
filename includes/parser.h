/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:38:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/07 13:02:44 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	int				heredoc_fd;
	struct s_redir	*next;
}t_redir;

typedef struct s_cmd {
	char			**args;
	int				arg_count;
	t_redir			*redirections;
	int				has_heredoc;
	struct s_cmd	*next;
}t_cmd;

t_cmd	*create_cmd(int arg_count);
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

#endif
