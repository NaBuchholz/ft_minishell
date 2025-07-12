/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:29:16 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 17:29:46 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Clear heredoc interrupted flag
 * @param shell Pointer to shell structure
 */
void	clear_heredoc_interrupted(t_shell *shell)
{
	if (shell)
		shell->heredoc_interrupted = 0;
}
