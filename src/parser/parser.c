/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:34:22 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/16 15:07:45 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//  Implementar parse_pipeline() - conecta comandos
t_cmd	*parse_pipeline(t_token *tokens)
{
	t_cmd	*first_cmd;
	t_cmd	*current_cmd;
	t_cmd	*new_cmd;
	t_token	*current_token;

	if (!tokens)
		return (NULL);
	current_token = tokens;
	first_cmd = parse_simple_cmd(&current_token);
	if (!first_cmd)
		return (NULL);
	current_cmd = first_cmd;
	while (current_token)
	{
		new_cmd = parse_simple_cmd(&current_token);
		if (!new_cmd)
			break ;
		current_cmd->next = new_cmd;
		current_cmd = new_cmd;
	}
	return (first_cmd);
}
//  Implementar add_cmd_to_list() - adiciona cmd->next
