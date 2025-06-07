/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 09:44:34 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/07 10:08:26 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_cmd_lst(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("No commands found!!");
		return ;
	}
	i = 0;
	while (cmd)
	{
		ft_printf("----Debug command----\nCommand: %s\n", cmd->args[0]);
		if (cmd->arg_count > 1)
		{
			ft_printf("Argumentos: ");
			i = 1;
			while (i < cmd->arg_count)
			{
				ft_printf("%s", cmd->args[i]);
				if (i < cmd->arg_count - 1)
					ft_printf(" ");
				i++;
			}
		}
		cmd = cmd->next;
	}
}
