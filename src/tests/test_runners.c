/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_runners.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:30:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/03 09:11:25 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

int	test(void)
{
	int	failures;

	failures = 0;
	failures += run_token_creation_tests();
	failures += run_lexer_tests();
	failures += run_memory_tests();
	failures += run_heredoc_tests();
	return (failures);
}
