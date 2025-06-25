/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:59:25 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/24 21:29:52 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_shell
{
	char	*input;
	int		exit_status;
	int		should_exit;
	char	**envp;
}			t_shell;

/**
 * @brief Structure to hold expansion context
 * @param envp Environment variables array
 * @param exit_status Last Command exit status
 */
typedef struct s_exp_ctx
{
	char	**envp;
	int		exit_status;
}t_exp_ctx;

int			shell_loop(t_shell *shell, char **envp);
int			process_input(t_shell *shell, char **env);
void		update_exit_status(t_shell *shell, int status);
int			get_exit_status(t_shell *shell);
int			test(void);
void		syntax_error(char *token);
void		command_error(char *cmd, char *msg);
char		**cpy_env(char **envp);
void		free_cpy_env(char **env);
int			is_exit_cmd(char *input);

#endif
