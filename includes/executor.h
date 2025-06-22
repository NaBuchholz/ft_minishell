/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:50:26 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/22 12:31:21 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "minishell.h"
# include "parser.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>

/* ************************************************************************** */
/*                              EXECUTOR UTILS                               */
/* ************************************************************************** */

char	**cmd_to_argv(t_cmd *cmd);
void	free_argv(char **argv);

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
int		is_absolute_or_relative_path(char *cmd);
char	*build_full_path(char *dir, char *cmd_name);

/* ************************************************************************** */
/*                              ERROR HANDLING                               */
/* ************************************************************************** */

void	exec_error(char *cmd, char *msg, int exit_code);
int		handle_exec_error(char *cmd, int error_type);

#endif
