/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:55:10 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:06 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIROMENT_H
# define ENVIROMENT_H
# include "minishell.h"
# include "lexer.h"

int		expand_token_variables(t_token *tokens, char **env, int status);
char	*get_env_value(char const *name, char **envp);
int		set_env_var(char ***env, char *name, char *value);
int		unset_env_var(char ***env, char *name);
void	free_cpy_env(char **env);
char	**cpy_env(char **envp);
#endif
