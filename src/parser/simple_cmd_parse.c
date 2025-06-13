/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:27:51 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/13 17:07:24 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Count redirection tokens between start and end positions
 * @param start Starting token to count from (inclusive)
 * @param end Ending token to stop before (exclusive) or NULL for end of list
 * @return Number of redirection tokens found in the range
 */
int	count_redirs_in_cmd(t_token *start, t_token *end)
{
	int	i;

	if (!start)
		return (0);
	i = 0;
	while (start && start != end)
	{
		if (is_redirection(start->type))
			i++;
		start = start->next;
	}
	return (i);
}

/**
* @brief Count TOKEN_WORD tokens between start and end positions
* @param start Starting token to count from (inclusive)
* @param end Ending token to stop before (exclusive) or NULL for end of list
* @return Number of TOKEN_WORD tokens found in the range
*/
static int	count_words_between(t_token *start, t_token *end)
{
	int		count;
	t_token	*temp;

	if (!start)
		return (0);
	count = 0;
	temp = start;
	while (temp && temp != end)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief Collect command arguments from token range into string array
 * @param start Starting token to collect from (inclusive)
 * @param end Ending token to stop before (exclusive) or NULL for end of list
 * @return Allocated array of strings terminated with NULL, or NULL on error
 */
static void	collect_command_args(t_cmd *cmd, t_token *start, t_token *end)
{
	t_token	*temp;

	temp = start;
	while (temp && temp != end)
	{
		if (temp->type == TOKEN_WORD)
			add_arg_to_cmd(cmd, create_arg(temp->value, 0, 0));
		else if (temp->type == TOKEN_SINGLE_QUOTE)
			add_arg_to_cmd(cmd, create_arg(temp->value, 1, 1));
		else if (temp->type == TOKEN_DOUBLE_QUOTE)
			add_arg_to_cmd(cmd, create_arg(temp->value, 1, 2));
		temp = temp->next;
	}
	debug_args_list(cmd->args);
}

t_cmd	*parse_simple_cmd(t_token **current)
{
	t_token	*end;
	t_cmd	*cmd;
	t_token	**temp_curr;

	if (!current || !(*current))
		return (NULL);
	end = find_next_pipe(*current);
	cmd = create_cmd(count_words_between(*current, end));
	if (!cmd)
		return (NULL);
	collect_command_args(cmd, (*current), end);
	if (!cmd->args)
	{
		free_cmd(cmd);
		return (NULL);
	}
	temp_curr = current;
	cmd->redirections = parse_redirs(temp_curr, end);
	if (end && end->type == TOKEN_PIPE)
		(*current) = end->next;
	else
		*current = NULL;
	return (cmd);
}
