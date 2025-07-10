/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:38:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/09 22:34:34 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"
# include "environment.h"

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
}	t_redir;

/**
 * @brief Structure representing a command argument
 * @param value Argument value
 * @param is_quote Number of arguments in the command
 * @param quote_type Type of quote, single or doble.
 * @param next Pointer to next command in pipeline
 */
typedef struct s_arg
{
	char			*value;
	int				is_quote;
	int				quote_type;
	struct s_arg	*next;
}	t_arg;

/**
 * @brief Structure representing a command
 * @param args Array of command arguments (argv style)
 * @param arg_count Number of arguments in the command
 * @param redirections List of redirections for this command
 * @param has_heredoc Flag indicating if command has heredoc
 * @param next Pointer to next command in pipeline
 */
typedef struct s_cmd
{
	t_arg			*args;
	int				arg_count;
	t_redir			*redirections;
	int				has_heredoc;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*create_cmd(void);
void	free_cmd(t_cmd *cmd);
void	free_cmd_lst(t_cmd *cmd);
void	free_arg(t_arg *arg);
int		is_redirection(t_token_type type);
int		count_cmds(t_cmd *cmd);
void	add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir);
t_token	*find_next_pipe(t_token *start);
int		count_args(t_token *start);
int		validate_redir_target(t_token *target_token);
int		count_redirs_in_cmd(t_token *start, t_token *end);
t_cmd	*parse_simple_cmd(t_token **current);
t_redir	*create_redir(t_token_type type, char *target);
t_redir	*parse_single_redir(t_token **current);
t_redir	*parse_redirs(t_token *start, t_token *end);
t_token	*validate_syntax(t_token *tokens);
t_arg	*create_arg(char *value, int is_quoted, int quote_type);
void	free_args_lst(t_arg *args);
void	add_arg_to_cmd(t_cmd *cmd, t_arg *new_arg);
void	free_redir_lst(t_redir *redir);
void	debug_args_list(t_arg *args);
t_cmd	*parse_pipeline(t_token *tokens);
int		append_text(char **res, char const *input, int start, int len);
char	*get_env_value(char const *name, char **envp);
int		append_var(char **res, char const *name, t_exp_ctx *ctx);
char	*get_var_name(char const *input, int *i);
int		is_variable_start(char const *input, int i);
int		expand_single_var(char **res, char const *input,
			int *i, t_exp_ctx *ctx);
int		process_var_expansion(char **res, char const *input, int *i, int *last);
char	*finalize_expansion(char *res, char const *input,
			int last, int i);
int		process_expansion_loop(char **res, char const *input,
			t_exp_ctx *ctx, int *indices);
char	*process_expansion_with_ctx(char const *input, t_exp_ctx *ctx);
char	*expand_variables(char const *input, char **envp, int status);
int		expand_token(t_token *token, char **envp, int status);
int		expand_tokens(t_token *tokens, char **envp, int status);
int		is_exit_status(const char *str, int i);
int		contains_exit_status(const char *str);
char	*extract_segment(const char *str, int start, int len);
char	*append_strings(char *s1, char *s2);
char	*expand_exit_status(const char *str, int status);
char	*process_exit_value(char *result, const char *str, int status);
int		expand_token_exit(t_token *token, int status);
int		expand_tokens_exit(t_token *tokens, int status);
int		apply_exit_status(t_token *tokens, t_shell *shell);
void	init_expansion(char **result, int *i, int *last);
int		handle_segment(char **result, const char *str, int *positions);
char	*process_exit_status(char *result, const char *str, int status);
int		append_status(char **result, int status);
int		append_segment(char **result, const char *str, int start, int end);
t_token	*validate_token_syntax(t_token *tokens);

#endif
