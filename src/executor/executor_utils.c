/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:50:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 12:54:21 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**cmd_to_argv(t_cmd *cmd)
{
	char	**argv;
	t_arg	*current;
	int		i;

	if (!cmd || !cmd->args)
		return (NULL);
	argv = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	i = 0;
	current = cmd->args;
	while (current)
	{
		argv[i++] = ft_strdup(current->value);
		current = current->next;
	}
	return (argv);
}

void	free_argv(char **argv)
{
	int	i;

	if (!argv)
		return ;
	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
}
