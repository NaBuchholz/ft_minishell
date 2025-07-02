/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:55:10 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/01 22:51:32 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include "minishell.h"
# include "lexer.h"

int	expand_token_variables(t_token *tokens, char **env, int status);
int	builtin_env(char **argv, char **envp);
int		expand_token_variables(t_token *tokens, char **env, int status);
char	*get_env_value(char const *name, char **envp);
int		count_env_vars(char **env);
int		set_env_var(char ***env, char *name);
int		unset_env_var(char ***env, char *name);
int		env_set(char ***env, char *name, char *value);
void	free_cpy_env(char **env);
int		find_index(char **env, char *name);
char	*create_env_string(char *name, char *value);
char	**cpy_env(char **envp);
int		validate_env_params(char ***env, char *name);
int		builtin_env(char **argv, char **envp);

#endif
