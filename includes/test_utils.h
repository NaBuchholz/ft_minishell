/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:27:07 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:10:14 by nbuchhol         ###   ########.fr       */
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
int		cleanup_and_return(t_token *tokens, char *msg, int result, t_cmd *cmd);
int		test_append_operator_basic(void);
int		test_append_with_spaces(void);
int		test_append_vs_redirect(void);
int		test_append_command(void);
int		test_triple_redirect_edge_case(void);

#endif
