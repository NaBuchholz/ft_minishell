/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:05:24 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/10 09:22:21 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	cleanup_and_return(t_token *tokens, char *msg, int result, t_cmd *cmd)
{
	if (cmd)
		free_cmd(cmd);
	if (tokens)
		free_token_list(tokens);
	if (result == 0)
		printf("✅ PASS: %s\n", msg);
	else
		printf("❌ FAIL: %s\n", msg);
	return (result);
}
