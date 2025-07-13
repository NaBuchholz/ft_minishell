/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:50:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 13:23:32 by nbuchhol         ###   ########.fr       */
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

int	handle_exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (130);
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			return (131);
		}
		else
			return (128 + WTERMSIG(status));
	}
	return (1);
}
