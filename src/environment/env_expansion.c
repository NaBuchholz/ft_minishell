/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 15:54:34 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/07/13 17:43:57 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "parser.h"

int	expand_token_variables(t_token *tokens, char **env, int status)
{
	if (expand_tokens(tokens, env, status) != 0)
		return (1);
	return (0);
}
