/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:44:41 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 13:10:38 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_arg	*create_arg(char *value, int is_quoted, int quote_type)
{
	t_arg	*arg;

	if (!value)
		return (NULL);
	arg = ft_calloc(1, sizeof(t_arg));
	if (!arg)
		return (NULL);
	arg->value = ft_strdup(value);
	if (!arg->value)
	{
		free(arg);
		return (NULL);
	}
	arg->is_quote = is_quoted;
	arg->quote_type = quote_type;
	arg->next = NULL;
	return (arg);
}

void	add_arg_to_cmd(t_cmd *cmd, t_arg *new_arg)
{
	t_arg	*last;

	if (!cmd || !new_arg)
		return ;
	if (cmd->args == NULL)
		cmd->args = new_arg;
	else
	{
		last = cmd->args;
		while (last->next)
			last = last->next;
		last->next = new_arg;
	}
	cmd->arg_count++;
}

void	free_arg(t_arg *arg)
{
	if (!arg)
		return ;
	if (arg->value)
		free(arg->value);
	free(arg);
}

void	free_args_lst(t_arg *args)
{
	t_arg	*current;
	t_arg	*next;

	current = args;
	while (current)
	{
		next = current->next;
		free_arg(current);
		current = next;
	}
}
