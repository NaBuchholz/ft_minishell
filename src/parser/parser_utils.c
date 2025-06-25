/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:58:35 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/22 16:19:05 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (cmd->next)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

void	add_redir_to_cmd(t_cmd *cmd, t_redir *new_redir)
{
	t_redir	*last;

	if (!cmd || !new_redir)
		return ;
	if (!cmd->redirections)
	{
		cmd->redirections = new_redir;
		if (new_redir->type == TOKEN_HEREDOC)
			cmd->has_heredoc = 1;
	}
	else
	{
		last = cmd->redirections;
		while (last->next)
			last = last->next;
		last->next = new_redir;
		if (new_redir->type == TOKEN_HEREDOC)
			cmd->has_heredoc = 1;
	}
}

t_token	*find_next_pipe(t_token *start)
{
	if (!start)
		return (NULL);
	while (start && start->type != TOKEN_PIPE)
		start = start->next;
	return (start);
}

int	count_args(t_token *start)
{
	int	count;

	count = 0;
	while (start && start->type == TOKEN_WORD)
	{
		count++;
		start = start->next;
	}
	return (count);
}

/**
 * @brief Convert token type to its string representation.
 * @param type Token type to convert.
 * @return String representation of the token type.
 */
char	*token_type_to_symbol(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return ("|");
	if (type == TOKEN_REDIR_OUT)
		return (">");
	if (type == TOKEN_REDIR_IN)
		return ("<");
	if (type == TOKEN_REDIR_APPEND)
		return (">>");
	if (type == TOKEN_HEREDOC)
		return ("<<");
	return ("?");
}

