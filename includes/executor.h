/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:50:26 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/26 19:14:52 by vinda-si         ###   ########.fr       */
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

/* ************************************************************************** */
/*                              EXECUTOR UTILS                               */
/* ************************************************************************** */

char	**cmd_to_argv(t_cmd *cmd);
void	free_argv(char **argv);
int		apply_redirs(t_redir *redirections);

/* ************************************************************************** */
/*                              EXECUTOR CORE                                */
/* ************************************************************************** */

int		execute_external(t_cmd *cmd, char **env, int *exit_status);
int		wait_for_child(pid_t pid);
int		execute_command(t_cmd *cmd);

/* ************************************************************************** */
/*                              PATH RESOLUTION                              */
/* ************************************************************************** */

char	*find_executable(char *cmd_name, char **env);
int		is_executable(char *path);
char	*build_full_path(char *dir, char *cmd_name);

/* ************************************************************************** */
/*                                BUILT-INS                                   */
/* ************************************************************************** */

int		dispatch_builtin(t_cmd *cmd, char **env, int *exit_status);

/* ************************************************************************** */
/*                              ERROR HANDLING                               */
/* ************************************************************************** */

void	exec_error(char *cmd, char *msg, int exit_code);
int		handle_exec_error(char *cmd, int error_type);

#endif
