/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 08:33:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/05/31 14:50:14 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Process the input and send to lexer analysis.
 * @param t_shell pointer to base struct to shell variables.
 * @return 1 if the shell should exit, otherwise 0.
 */
int	process_input(t_shell *shell)
{
	printf("Você digitou: %s\n", shell->input);
	return (0);
}
