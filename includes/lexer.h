/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 14:00:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/06 21:54:11 by vinda-si         ###   ########.fr       */
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
	TOKEN_HEREDOC,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE
}					t_token_type;

typedef struct s_heredoc
{
	char	*delimiter;
	char	*content;
	int		fd;
}	t_heredoc;
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
int				ft_process_single_quote(const char *input, int *index, t_token **token_list);
t_token			*create_token(t_token_type type, char *value);
t_token			*tokenize_input(char *input);
int				get_word_length(char *input, int start);
void			free_token_list(t_token *tokens);
int				run_lexer_tests(void);

#endif
