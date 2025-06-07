/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:25:58 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/07 10:58:04 by nbuchhol         ###   ########.fr       */
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
