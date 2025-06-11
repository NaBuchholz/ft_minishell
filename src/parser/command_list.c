/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:44:41 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/06 17:47:05 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//  Implementar create_redir() - aloca e inicializa t_redir

void	free_redir_lst(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->target)
			free(current->target);
		free(current);
		current = next;
	}
}

t_redir	*create_redir(t_token_type type, char *target)
{
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	if (target)
	{
		redir->target = ft_strdup(target);
		if (!redir->target)
		{
			free(redir);
			return (NULL);
		}
	}
	redir->heredoc_fd = -1;
	return (redir);
}

t_cmd	*create_cmd(int arg_count)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (arg_count > 0)
	{
		cmd->args = ft_calloc(arg_count + 1, sizeof(char *));
		if (!cmd->args)
		{
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	if (cmd->redirections)
		free_redir_lst(cmd->redirections);
	free(cmd);
}

void	free_cmd_lst(t_cmd *cmd)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd;
	while (current)
	{
		next = current->next;
		free_cmd(current);
		current = next;
	}
}
