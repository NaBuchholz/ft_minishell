/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:58:35 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/07 09:55:39 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//  Criar count_commands() - conta cmds na lista
//  Criar get_next_token() - helper para navegação
//  Criar syntax_error() - mensagem padronizada

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
