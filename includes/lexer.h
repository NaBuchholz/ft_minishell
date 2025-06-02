/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:00:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 20:46:22 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

int				skip_whitespace(char *input, int pos);
int				is_operator(char c);
void			free_token(t_token *token);
t_token_type	get_operator_type(char *input, int pos);
void			add_token_to_list(t_token **head, t_token *new_token);
t_token			*create_token(t_token_type type, char *value);
t_token			*tokenize_input(char *input);
int				get_word_length(char *input, int start);
void			free_token_list(t_token *tokens);
int				run_lexer_tests(void);

#endif
