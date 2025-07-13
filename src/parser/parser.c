/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:34:22 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 13:11:54 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

t_token	*parser_and_expand(char *input, t_shell *shell)
{
	t_token	*tokens;

	if (!input || !shell)
		return (NULL);
	tokens = tokenize_input(input);
	if (!tokens)
		return (NULL);
	if (apply_exit_status(tokens, shell) != 0)
	{
		free_token_list(tokens);
		return (NULL);
	}
	return (tokens);
}
