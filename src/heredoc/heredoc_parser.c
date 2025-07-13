/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:07:47 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/10 13:07:55 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/01/10 10:00:00 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Extracts delimiter from heredoc token
 * @param token Pointer to token containing delimiter
 * @return Delimiter string or NULL on failure
 */
char	*extract_heredoc_delimiter(t_token *token)
{
	if (!token || !token->value)
		return (NULL);
	if (token->type != TOKEN_WORD && token->type != TOKEN_SINGLE_QUOTE
		&& token->type != TOKEN_DOUBLE_QUOTE)
		return (NULL);
	return (ft_strdup(token->value));
}

/**
 * @brief Creates heredoc structure from delimiter token
 * @param delimiter_token Token containing the heredoc delimiter
 * @return Pointer to heredoc structure or NULL on failure
 */
static t_heredoc	*create_heredoc_from_token(t_token *delimiter_token)
{
	char		*raw_delimiter;
	char		*clean_delimiter;
	int			is_quoted;
	t_heredoc	*heredoc;

	raw_delimiter = extract_heredoc_delimiter(delimiter_token);
	if (!raw_delimiter)
		return (NULL);
	is_quoted = is_heredoc_delimiter_quoted(raw_delimiter);
	clean_delimiter = normalize_delimiter(raw_delimiter);
	free(raw_delimiter);
	if (!clean_delimiter)
		return (NULL);
	if (!validate_heredoc_delimiter(clean_delimiter))
	{
		free(clean_delimiter);
		return (NULL);
	}
	heredoc = create_heredoc(clean_delimiter, is_quoted);
	free(clean_delimiter);
	return (heredoc);
}

/**
 * @brief Sets up heredoc structure for a redirection
 * @param redir Pointer to redirection structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
int	setup_heredoc_for_redir(t_redir *redir, t_shell *shell)
{
	t_token		*delimiter_token;
	t_heredoc	*heredoc;

	if (!redir || !shell || redir->type != TOKEN_HEREDOC)
		return (1);
	if (!redir->target)
		return (1);
	delimiter_token = create_token(TOKEN_WORD, redir->target);
	if (!delimiter_token)
		return (1);
	heredoc = create_heredoc_from_token(delimiter_token);
	free_token(delimiter_token);
	if (!heredoc)
		return (1);
	redir->heredoc = heredoc;
	return (0);
}

/**
 * @brief Prepares heredoc data during parsing phase
 * @param redir Pointer to redirection structure
 * @param shell Pointer to shell structure
 * @return 0 on success, 1 on failure
 */
int	prepare_heredoc_data(t_redir *redir, t_shell *shell)
{
	if (!redir || !shell)
		return (1);
	if (redir->type != TOKEN_HEREDOC)
		return (0);
	return (setup_heredoc_for_redir(redir, shell));
}

/**
 * @brief Counts heredoc redirections in a command
 * @param cmd Pointer to command structure
 * @return Number of heredoc redirections found
 */
int	count_heredocs_in_cmd(t_cmd *cmd)
{
	t_redir	*current;
	int		count;

	if (!cmd)
		return (0);
	count = 0;
	current = cmd->redirections;
	while (current)
	{
		if (current->type == TOKEN_HEREDOC)
			count++;
		current = current->next;
	}
	return (count);
}
