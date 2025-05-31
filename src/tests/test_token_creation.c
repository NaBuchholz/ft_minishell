/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token_creation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:25:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/05/31 19:50:41 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

static int	test_create_token_with_value(void)
{
	t_token	*token;

	token = create_token(TOKEN_WORD, "hello");
	debug_token(token);
	if (!token || token->type != TOKEN_WORD)
		return (1);
	free_token(token);
	return (0);
}

static int	test_create_token_without_value(void)
{

}

static int	test_create_token_edge_cases(void)
{

}

int	run_token_creation_tests(void)
{
	int	failures;

	failures = 0;
	printf("=== Running Token Creation Tests ===\n");
	failures += test_create_token_with_value();
	return (failures);
}
