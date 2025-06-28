/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:27:07 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/28 19:47:41 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_UTILS_H
# define TEST_UTILS_H
# include "lexer.h"
# include "parser.h"

void	debug_token(t_token *token);
void	debug_token_list(t_token *tokens);
char	*token_type_to_string(t_token_type type);
int		assert_token_equals(t_token *token, t_token_type type, char *value);
int		run_token_creation_tests(void);
int		run_memory_tests(void);
int		run_heredoc_tests(void);
int		run_parser_tests(void);
int		run_argument_tests(void);
int		run_arg_utils_tests(void);
int		cleanup_and_return(t_token *tokens, char *msg, int result, t_cmd *cmd);
int		test_append_operator_basic(void);
int		test_append_with_spaces(void);
int		test_append_vs_redirect(void);
int		test_append_command(void);
int		test_valid_syntax(void);
int		test_invalid_pipe_start(void);
int		test_consecutive_pipes(void);
int		test_invalid_redirection(void);
int		test_triple_redirect_edge_case(void);
int		run_argument_tests(void);
int		run_arg_utils_tests(void);
int		test_create_arg_basic(void);
int		test_create_quoted_arg(void);
int		test_create_arg_null_value(void);
int		test_create_arg_empty_string(void);
int		test_arg_single_quote_type(void);
int		test_add_arg_to_cmd_first(void);
int		test_add_multiple_args_to_cmd(void);
int		test_free_args_list(void);
int		test_add_arg_null_cases(void);
int		test_arg_list_traversal(void);
int		test_simple_output_redirect(void);
int		test_simple_input_redirect(void);
int		test_append_redirect(void);
int		test_multiple_redirects(void);
int		test_redirect_without_target(void);
void	debug_cmd(t_cmd *cmd);
void	debug_cmd_list(t_cmd *cmd_list);
void	debug_redir_list(t_redir *redir);
int		test_env_get_existing_var(char **envp);
int		test_env_get_nonexistent_var(char **envp);
int		test_find_index_basic(char **envp);
int		validate_new_var(char **test_env);
int		test_env_set_new_variable(char **envp);
int		run_env_manager_tests(char **envp);
#endif
