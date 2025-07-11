/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:59:25 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/11 20:17:20 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_shell
{
	char	*input;
	int		exit_status;
	int		should_exit;
	char	**envp;
	int		heredoc_interrupted;
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
}	t_exp_ctx;

int			shell_loop(t_shell *shell, char **envp);
int			process_input(t_shell *shell, char **env);
int			test(char **env);
void		update_exit_status(t_shell *shell, int status);
int			get_exit_status(t_shell *shell);
void		syntax_error(char *token);
void		command_error(char *cmd, char *msg);
char		**cpy_env(char **envp);
void		free_cpy_env(char **env);
int			is_exit_cmd(char *input);
int			setup_interactive_signals(void);
int			setup_child_signals(void);
int			check_signals(t_shell *shell);
int			block_signals(void);
int			unblock_signals(void);

#endif
