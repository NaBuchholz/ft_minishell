/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_session.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/10 13:12:44 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Starts a heredoc session
 * @param session Pointer to session structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
int	start_heredoc_session(t_heredoc_session *session, t_shell *shell)
{
	if (!session || !shell)
		return (1);
	session->shell = shell;
	session->total_heredocs = 0;
	session->current_heredoc = 0;
	session->session_interrupted = 0;
	clear_heredoc_interrupted(shell);
	return (0);
}

/**
 * @brief Counts total heredocs in command pipeline
 * @param cmd_list Pointer to command list
 * @return Total number of heredocs
 */
static int	count_total_heredocs(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		total;

	total = 0;
	current = cmd_list;
	while (current)
	{
		total += count_heredocs_in_cmd(current);
		current = current->next;
	}
	return (total);
}

/**
 * @brief Processes heredocs for entire command pipeline
 * @param session Pointer to session structure
 * @param cmd_list Pointer to command list
 * @return 0 on success, 1 on failure
 */
int	process_heredoc_session(t_heredoc_session *session, t_cmd *cmd_list)
{
	t_cmd	*current;

	if (!session || !cmd_list)
		return (1);
	session->total_heredocs = count_total_heredocs(cmd_list);
	if (session->total_heredocs == 0)
		return (0);
	current = cmd_list;
	while (current && !session->session_interrupted)
	{
		if (count_heredocs_in_cmd(current) > 0)
		{
			if (execute_heredocs_for_cmd(current, session->shell) != 0)
			{
				session->session_interrupted = 1;
				return (1);
			}
		}
		current = current->next;
	}
	return (session->session_interrupted ? 1 : 0);
}

/**
 * @brief Ends heredoc session and cleans up
 * @param session Pointer to session structure
 */
void	end_heredoc_session(t_heredoc_session *session)
{
	if (!session)
		return ;
	if (session->shell)
		clear_heredoc_interrupted(session->shell);
	session->total_heredocs = 0;
	session->current_heredoc = 0;
	session->session_interrupted = 0;
}

/**
 * @brief Checks if session should be interrupted
 * @param session Pointer to session structure
 * @return 1 if should interrupt, 0 if not
 */
int	should_interrupt_session(t_heredoc_session *session)
{
	if (!session || !session->shell)
		return (1);
	if (check_heredoc_interrupted(session->shell))
	{
		session->session_interrupted = 1;
		return (1);
	}
	return (0);
}
