/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:27:51 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/09 15:15:04 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
* @brief Skip tokens until finding a pipe or reaching end of list.
* @param current Starting token to search from.
* @return Pointer to pipe token if found, NULL if no pipe or invalid input.
*/
static t_token	*skip_next_pipe(t_token *current)
{
	if (!current)
		return (NULL);
	while (current->next && current->type == TOKEN_PIPE)
		current = current->next;
	return (current);
}

/**
 * @brief Count redirection tokens between start and end positions
 * @param start Starting token to count from (inclusive)
 * @param end Ending token to stop before (exclusive) or NULL for end of list
 * @return Number of redirection tokens found in the range
 */
int	count_redirs_in_cmd(t_token *start, t_token *end)
{
	int	i;

	i = 0;
	while (start && start != end)
	{
		if (is_redirection(start->type))
			i++;
		start = start->next;
	}
	return (i);
}

/**
* @brief Count TOKEN_WORD tokens between start and end positions
* @param start Starting token to count from (inclusive)
* @param end Ending token to stop before (exclusive) or NULL for end of list
* @return Number of TOKEN_WORD tokens found in the range
*/
static int	count_words_between(t_token *start, t_token *end)
{
	int		count;
	t_token	*temp;

	if (!start)
		return (0);
	count = 0;
	temp = start;
	while (temp && temp != end)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		temp = temp->next;
	}
	return (count);
}

/**
 * @brief Collect command arguments from token range into string array
 * @param start Starting token to collect from (inclusive)
 * @param end Ending token to stop before (exclusive) or NULL for end of list
 * @return Allocated array of strings terminated with NULL, or NULL on error
 */
static char	**collect_command_args(t_token *start, t_token *end)
{
	size_t	word_count;
	char	**args;
	t_token	*temp;
	int		i;

	if (!start)
		return (NULL);
	word_count = count_words_between(start, end);
	args = ft_calloc(word_count + 1, sizeof(char *));
	if (!args)
		return (NULL);
	temp = start;
	i = 0;
	while (temp && temp != end)
	{
		if (temp->type == TOKEN_WORD)
			args[i++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	return (args);
}

t_cmd	*parse_simple_cmd(t_token **current)
{
	t_token	*end;
	t_cmd	*cmd;

	if (!current || !(*current))
		return (NULL);
	end = skip_next_pipe(*current);
	cmd = create_cmd(count_args(*current));
	if (!cmd)
		return (NULL);
	cmd->args = collect_command_args((*current), end);
// ### **6. Coletar redirecionamentos**
// - Usar função do arquivo `redirections.c` (que você vai fazer depois)
// - Atribuir para `cmd->redirections`
	cmd->redirections = parse
// ### **7. Atualizar ponteiro current**
// - **IMPORTANTE**: Avançar `*current` para o próximo comando
// - Se encontrou pipe, avança para depois do pipe
// - Se chegou ao fim, `*current` fica NULL

// ### **8. Tratamento de erros**
// - Se qualquer alocação falhar, limpar tudo que já foi alocado
// - Retornar NULL em caso de erro

// ### **9. Retorno**
// - Se tudo deu certo, retornar o `t_cmd` completo

// **Essa função é como um "maestro" que coordena todas as outras!**
}
