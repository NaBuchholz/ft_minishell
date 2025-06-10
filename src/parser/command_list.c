/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:44:41 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 14:32:41 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		free_args_lst(cmd->args);
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
