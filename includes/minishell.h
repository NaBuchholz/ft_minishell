/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:59:25 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/21 23:20:01 by vinda-si         ###   ########.fr       */
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

int			shell_loop(t_shell *shell);
int			process_input(t_shell *shell);
void		update_exit_status(t_shell *shell, int status);
int			get_exit_status(t_shell *shell);
int			test(void);
void		syntax_error(char *token);
void		command_error(char *cmd, char *msg);

#endif
