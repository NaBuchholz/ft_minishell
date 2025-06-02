/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cleanup_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:05:24 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/02 18:06:26 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test_cleanup_and_return(t_token *tokens, char *msg, int result)
{
	if (result == 0)
		printf("✅ PASS: %s\n", msg);
	else
		printf("❌ FAIL: %s\n", msg);
	free_token_list(tokens);
	return (result);
}
