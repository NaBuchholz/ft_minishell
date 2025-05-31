/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:14:04 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/05/31 18:24:46 by nbuchhol         ###   ########.fr       */
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

void	debug_token_list(t_token *tokens){

};

int	assert_token_equals(t_token *token, t_token_type type, char *value){

};
