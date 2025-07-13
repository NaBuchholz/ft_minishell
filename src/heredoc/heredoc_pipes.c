/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 10:00:00 by vinda-si          #+#    #+#             */
/*   Updated: 2025/07/10 13:10:53 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"

/**
 * @brief Creates a pipe for heredoc content
 * @param heredoc Pointer to heredoc structure
 * @return 0 on success, 1 on failure
 */
int	create_heredoc_pipe(t_heredoc *heredoc)
{
	int	pipe_fds[2];

	if (!heredoc)
		return (1);
	if (pipe(pipe_fds) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	heredoc->fd = pipe_fds[0];
	return (pipe_fds[1]);
}

/**
 * @brief Writes content to pipe file descriptor
 * @param fd File descriptor to write to
 * @param content Content string to write
 * @return 0 on success, 1 on failure
 */
int	write_content_to_pipe(int fd, char *content)
{
	size_t	content_len;
	ssize_t	bytes_written;

	if (fd < 0 || !content)
		return (1);
	content_len = ft_strlen(content);
	if (content_len == 0)
	{
		close(fd);
		return (0);
	}
	bytes_written = write(fd, content, content_len);
	close(fd);
	if (bytes_written == -1)
	{
		perror("minishell: write");
		return (1);
	}
	if ((size_t)bytes_written != content_len)
		return (1);
	return (0);
}

/**
 * @brief Closes heredoc pipe file descriptor
 * @param heredoc Pointer to heredoc structure
 */
void	close_heredoc_pipe(t_heredoc *heredoc)
{
	if (!heredoc)
		return ;
	if (heredoc->fd >= 0)
	{
		close(heredoc->fd);
		heredoc->fd = -1;
	}
}

/**
 * @brief Sets up complete pipe system for heredoc
 * @param heredoc Pointer to heredoc structure
 * @return 0 on success, 1 on failure
 */
int	setup_heredoc_pipe_system(t_heredoc *heredoc)
{
	int	write_fd;

	if (!heredoc || !heredoc->content)
		return (1);
	write_fd = create_heredoc_pipe(heredoc);
	if (write_fd < 0)
		return (1);
	if (write_content_to_pipe(write_fd, heredoc->content) != 0)
	{
		close_heredoc_pipe(heredoc);
		return (1);
	}
	return (0);
}

/**
 * @brief Validates pipe file descriptor
 * @param fd File descriptor to validate
 * @return 1 if valid, 0 if invalid
 */
int	validate_pipe_fd(int fd)
{
	return (fd >= 0);
}
