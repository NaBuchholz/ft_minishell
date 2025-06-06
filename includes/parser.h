/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:38:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/06 15:18:43 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "lexer.h"


typedef struct s_redir
{
	t_token_type	type;
	char			*filename;
	struct s_redir	*next;
}t_redir;

typedef struct s_cmd
{
	char				**args;
	char				*input_file;
	char				*output_file;
	char				*append_file;
	t_heredoc			*heredoc;
	int					builtin_type;
	struct s_command	*next;
}t_cmd;



#endif

