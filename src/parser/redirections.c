/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:25:58 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/09 15:17:49 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//  Criar get_redir_filename() - pega próximo WORD
//  Implementar collect_redirections() - extrai todas
//  Implementar add_redir_to_list() - adiciona na lista
//  Tratar erro de redir sem filename

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
t_redir *parse_single_redir(t_token **current)
{
    // FAZER: Cria t_redir com target, avança current
	t_redir	*redir;

	if (!current || !(*current))
		return (NULL);
	if (!is_redirection_token((*current)->type)
		|| !validate_redir_target((*current)->next))
		return (NULL);
	redir = create_redir((*current)->type, (*current)->next->value);
	if (!redir)
		return (NULL);
	*current = (*current)->next->next;
	return (redir);
}

t_redir *parse_redirs(t_token **current, t_token *end)
{
    // Loop que chama parse_single_redir várias vezes
    // Monta lista ligada de redirecionamentos
}
