/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:14:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 14:13:58 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_utils.h"

char	*token_type_to_string(t_token_type type)
{
	if (type == TOKEN_WORD)
		return ("WORD");
	else if (type == TOKEN_PIPE)
		return ("PIPE");
	else if (type == TOKEN_REDIR_IN)
		return ("REDIR_IN");
	else if (type == TOKEN_REDIR_OUT)
		return ("REDIR_OUT");
	else
		return ("UNKNOWN");
};

void	debug_token(t_token *token)
{
	printf("-------DEBUG TOKEN-------\n");
	if (!token)
	{
		printf("No token found!!!!\n");
		return ;
	}
	printf("Token Type: %s \n", token_type_to_string(token->type));
	printf("Token Value: %s \n", token->value);
};

void	debug_token_list(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	printf("=== TOKEN LIST DEBUG ===\n");
	while (current)
	{
		printf("Token %d: %s", count, token_type_to_string(current->type));
		if (current->value)
			printf(" (value: %s)", current->value);
		printf("\n");
		current = current->next;
		count++;
	}
	printf("Total tokens: %d\n", count);
}

int	assert_token_equals(t_token *token, t_token_type type, char *value)
{

}
