/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:04:38 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 10:39:46 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "minishell.h"
# include "lexer.h"
# include "parser.h"
# include <signal.h>

# define HEREDOC_PROMPT "> "
# define MAX_HEREDOC_SIZE 1048576

/**
 * @brief Context structure for heredoc processing
 */
typedef struct s_heredoc_ctx
{
	t_shell		*shell;
	t_heredoc	*heredoc;
	char		**envp;
	int			exit_status;
}	t_heredoc_ctx;

/**
 * @brief Session management for multiple heredocs
 */
typedef struct s_heredoc_session
{
	t_shell		*shell;
	int			total_heredocs;
	int			current_heredoc;
	int			session_interrupted;
}	t_heredoc_session;

/* ************************************************************************** */
/*                              HEREDOC CORE                                 */
/* ************************************************************************** */

int			process_heredoc_with_context(t_heredoc_ctx *ctx);
int			read_heredoc_content(t_heredoc_ctx *ctx);
char		*read_heredoc_line_safe(t_shell *shell);
int			is_delimiter_match(char *line, char *delimiter);
char		*join_heredoc_lines(char **lines, int count);

/* ************************************************************************** */
/*                              HEREDOC UTILS                                */
/* ************************************************************************** */

void		free_heredoc(t_heredoc *heredoc);
int			validate_heredoc_delimiter(char *delimiter);
char		*normalize_delimiter(char *raw_delimiter);
int			is_heredoc_delimiter_quoted(char *delimiter);
int			count_heredocs_in_cmd(t_cmd *cmd);
t_heredoc	*create_heredoc(char *delimiter, int is_quoted);

/* ************************************************************************** */
/*                              HEREDOC PARSER                               */
/* ************************************************************************** */

char		*extract_heredoc_delimiter(t_token *token);
int			setup_heredoc_for_redir(t_redir *redir, t_shell *shell);
int			prepare_heredoc_data(t_redir *redir, t_shell *shell);

/* ************************************************************************** */
/*                              HEREDOC EXPANSION                            */
/* ************************************************************************** */

char		*expand_heredoc_content(char *content, t_heredoc_ctx *ctx);
int			should_expand_heredoc_content(int is_quoted);

/* ************************************************************************** */
/*                              HEREDOC PIPES                                */
/* ************************************************************************** */

int			create_heredoc_pipe(t_heredoc *heredoc);
int			write_content_to_pipe(int fd, char *content);
void		close_heredoc_pipe(t_heredoc *heredoc);
int			setup_heredoc_pipe_system(t_heredoc *heredoc);

/* ************************************************************************** */
/*                              HEREDOC EXECUTOR                             */
/* ************************************************************************** */

int			execute_heredocs_for_cmd(t_cmd *cmd, t_shell *shell);
int			process_single_heredoc(t_redir *redir, t_shell *shell);
int			handle_heredoc_redir(t_redir *redir);
void		cleanup_heredoc_fds(t_cmd *cmd);

/* ************************************************************************** */
/*                              HEREDOC SIGNALS                              */
/* ************************************************************************** */

int			setup_heredoc_signals(t_shell *shell);
int			restore_interactive_signals(t_shell *shell);
int			check_heredoc_interrupted(t_shell *shell);
void		set_heredoc_interrupted(t_shell *shell);
void		clear_heredoc_interrupted(t_shell *shell);

/* ************************************************************************** */
/*                              HEREDOC SESSION                              */
/* ************************************************************************** */

int			start_heredoc_session(t_heredoc_session *session, t_shell *shell);
int			process_heredoc_session(t_heredoc_session *session, t_cmd *cmd);
void		end_heredoc_session(t_heredoc_session *session);
int			validate_pipe_fd(int fd);
#endif
