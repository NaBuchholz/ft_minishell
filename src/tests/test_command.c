/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 14:30:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/15 13:24:38 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

void	debug_redir_list(t_redir *redir)
{
	int	count;

	count = 0;
	printf("=== REDIRECTIONS DEBUG ===\n");
	while (redir)
	{
		printf("Redir %d: %s -> %s\n", count,
			token_type_to_string(redir->type), redir->target);
		redir = redir->next;
		count++;
	}
	printf("Total redirections: %d\n", count);
	printf("===========================\n");
}

void	debug_cmd(t_cmd *cmd)
{
	printf("=== COMMAND DEBUG ===\n");
	if (!cmd)
	{
		printf("No command found!\n");
		return ;
	}
	printf("Command args:\n");
	debug_args_list(cmd->args);
	printf("Command redirections:\n");
	debug_redir_list(cmd->redirections);
	printf("Arg count: %d\n", cmd->arg_count);
	if (cmd->has_heredoc)
		printf("Has heredoc: yes\n");
	else
		printf("Has heredoc: no\n");
	printf("======================\n");
}

void	debug_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		count;

	current = cmd_list;
	count = 0;
	printf("=== COMMAND LIST DEBUG ===\n");
	while (current)
	{
		printf("\n--- Command %d ---\n", count);
		debug_cmd(current);
		current = current->next;
		count++;
	}
	printf("Total commands: %d\n", count);
	printf("===========================\n");
}
