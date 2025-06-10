/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 14:44:41 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 14:29:23 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_arg	*create_arg(char *value, int is_quoted, int quote_type)
{

}

void	add_arg_to_cmd(t_cmd *cmd, t_arg *new_arg)
{

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
