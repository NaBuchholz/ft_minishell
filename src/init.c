/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/16 15:17:13 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test_utils.h"

/**
 * @brief Process the input and send to lexer analysis.
 * @param t_shell pointer to base struct to shell variables.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	process_input(t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (ft_strncmp(shell->input, "exit", 4) == 0)
	{
		shell->should_exit = 1;
		return (1);
	}
	tokens = tokenize_input(shell->input);
	if (tokens)
	{
		debug_token_list(tokens);
		cmd = parse_pipeline(tokens);
		if (cmd)
		{
			debug_cmd_list(cmd);
			free_cmd(cmd);
		}
	}
	else
		printf("❌ No tokens created\n");
	free_token_list(tokens);
	return (0);
}
