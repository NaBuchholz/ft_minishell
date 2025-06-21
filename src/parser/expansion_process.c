/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:38:51 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/16 21:15:18 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Expands single variable and update result
 * @param res Result string pointer
 * @param input Input string
 * @param i Current index pointer
 * @param ctx Expansion context (envp + exit_status)
 * @return 0 on success, 1 on error
 */
int	expand_single_var(char **res, char const *input, int *i, t_exp_ctx *ctx)
{
	char	*name;
	int		ret;

	name = get_var_name(input, i);
	if (!name)
		return (1);
	ret = append_var(res, name, ctx);
	free(name);
	return (ret);
}

/**
 * @brief Processes text before variable
 * @param res Result string pointer
 * @param input Input string
 * @param i Current index pointer
 * @return 0 on success, 1 on error
 */
int	process_var_expansion(char **res, char const *input, int *i, int *last)
{
	if (*i > *last)
		return (append_text(res, input, *last, *i - *last));
	return (0);
}

/**
 * @brief Finalizes expansion by appending remaining text
 * @param res Result string
 * @param input Input string
 * @param last Last processed index
 * @param i Current index
 * @return Final string or NULL on error
 */
char	*finalize_expansion(char *res, char const *input, int last, int i)
{
	if (last < i && append_text(&res, input, last, i - last))
	{
		free(res);
		return (NULL);
	}
	return (res);
}

/**
 * @brief Processes expansion loop core logic
 * @param res Result string pointer
 * @param input Input string
 * @param ctx Expansion context
 * @param indices Array containing i and last indices
 * @return 0 on success, 1 on error
 */
int	process_expansion_loop(char **res, char const *input, t_exp_ctx *ctx,
		int *indices)
{
	int	*i;
	int	*last;

	i = &indices[0];
	last = &indices[1];
	if (process_var_expansion(res, input, i, last) != 0)
		return (1);
	if (expand_single_var(res, input, i, ctx) != 0)
		return (1);
	*last = *i;
	return (0);
}

/**
 * @brief Main expansion function with context
 * @param input Input string with variables
 * @param ctx Expansion context
 * @return Expanded string or NULL on error
 */
char	*process_expansion_with_ctx(char const *input, t_exp_ctx *ctx)
{
	char	*res;
	int		indices[2];

	res = ft_strdup("");
	if (!res)
		return (NULL);
	indices[0] = 0;
	indices[1] = 0;
	while (input[indices[0]])
	{
		if (is_variable_start(input, indices[0]))
		{
			if (process_expansion_loop(&res, input, ctx, indices) != 0)
			{
				free(res);
				return (NULL);
			}
		}
		else
			indices[0]++;
	}
	return (finalize_expansion(res, input, indices[1], indices[0]));
}
