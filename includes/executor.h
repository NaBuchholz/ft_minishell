/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:50:26 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/12 12:00:23 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "parser.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>

/**
 * @brief Structure to hold pipeline execution context
 * @param pipes Array of pipe file descriptors
 * @param cmd_count Total number of commands in pipeline
 * @param env Environment variables
 */
typedef struct s_pipe_ctx
{
	int		*pipes;
	int		cmd_count;
}	t_pipe_ctx;

/* ************************************************************************** */
/*                              EXECUTOR UTILS                               */
/* ************************************************************************** */

char	**cmd_to_argv(t_cmd *cmd);
void	free_argv(char **argv);
int		apply_redirs(t_redir *redirections);
void	close_all_pipes(int *pipes, int pipe_count);
int		create_pipes(int **pipes, int pipe_count);
int		check_exit_builtin(char **argv, t_shell *shell);
void	print_sorted_env(char **envp);
int		check_pwd_builtin(char **argv, t_shell *shell);

/* ************************************************************************** */
/*                              EXECUTOR CORE                                */
/* ************************************************************************** */

int		execute_external(t_cmd *cmd, char **env, int *exit_status);
int		execute_pipeline(t_cmd *cmd_list, char **env, int *exit_status);
int		setup_child_pipes(int cmd_index, int cmd_count, int *pipes);
int		wait_all_processes(pid_t *pids, int cmd_count);
int		execute_command(t_cmd *cmd);
int		fork_and_execute(t_cmd *cmd_list, int *pipes, pid_t *pids, char **env);
int		builtin_unset(char **argv, t_shell *shell);
int		builtin_env(char **argv, char **envp);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_exit(char **argv, t_shell *shell);
int		builtin_pwd(char **argv, t_shell *shell);

/* ************************************************************************** */
/*                              PATH RESOLUTION                              */
/* ************************************************************************** */

char	*find_executable(char *cmd_name, char **env);
int		is_executable(char *path);
char	*build_full_path(char *dir, char *cmd_name);

/* ************************************************************************** */
/*                                BUILT-INS                                   */
/* ************************************************************************** */

int		dispatch_builtin(t_cmd *cmd, t_shell *shell, int *exit_status);
int		builtin_env(char **argv, char **envp);
int		builtin_export(char **argv, t_shell *shell);
int		builtin_unset(char **argv, t_shell *shell);
void	print_sorted_env(char **envp);

/* ************************************************************************** */
/*                              ERROR HANDLING                               */
/* ************************************************************************** */

void	exec_error(char *cmd, char *msg, int exit_code);
int		handle_exec_error(char *cmd, int error_type);

/* ************************************************************************** */
/*                              HEREDOC INTEGRATION                          */
/* ************************************************************************** */

int		execute_heredocs_for_cmd(t_cmd *cmd, t_shell *shell);
void	cleanup_heredoc_fds(t_cmd *cmd);
int		validate_heredoc_setup(t_cmd *cmd);

#endif
