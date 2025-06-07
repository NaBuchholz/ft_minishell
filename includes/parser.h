/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:38:45 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/06 20:06:18 by nbuchhol         ###   ########.fr       */
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
#endif
