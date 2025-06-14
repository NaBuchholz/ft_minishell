/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 14:20:26 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 14:20:44 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
