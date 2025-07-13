/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:25:58 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 13:12:11 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	validate_redir_target(t_token *target_token)
{
	if (!target_token || target_token->type != TOKEN_WORD)
		return (0);
	if (!target_token->value || target_token->value[0] == '\0')
		return (0);
	return (1);
}

int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

/**
 * @brief Parse a single redirection token and its target
 * @param current Pointer to current token (will be advanced)
 * @return Allocated t_redir structure or NULL on error
 */
t_redir	*parse_single_redir(t_token **current)
{
	t_redir	*redir;

	if (!current || !(*current))
		return (NULL);
	if (!is_redirection((*current)->type)
		|| !validate_redir_target((*current)->next))
		return (NULL);
	redir = create_redir((*current)->type, (*current)->next->value);
	if (!redir)
		return (NULL);
	*current = (*current)->next->next;
	return (redir);
}

static t_redir	*add_redir_to_list(t_redir *head, t_redir *new_redir)
{
	t_redir	*temp;

	if (!new_redir)
		return (head);
	if (!head)
		return (new_redir);
	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_redir;
	return (head);
}

t_redir	*parse_redirs(t_token *start, t_token *end)
{
	t_redir	*redir;
	t_redir	*head;
	t_token	*temp;

	head = NULL;
	temp = start;
	while (temp && temp != end)
	{
		if (is_redirection(temp->type))
		{
			if (!temp->next || temp->next == end
				|| !validate_redir_target(temp->next))
				return (NULL);
			redir = create_redir(temp->type, temp->next->value);
			if (!redir)
				return (NULL);
			head = add_redir_to_list(head, redir);
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (head);
}
