/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:59:25 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/21 12:37:39 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

typedef struct s_shell
{
	char	*input;
	int		exit_status;
	int		should_exit;
}			t_shell;

int			shell_loop(t_shell *shell);
int			process_input(t_shell *shell);
int			test(void);
void		syntax_error(char *token);
void		command_error(char *cmd, char *msg);

#endif
