/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 22:25:19 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/15 23:58:31 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Processes variable expansion in loop
 * @param input Inout string
 * @param envp Environment variables
 * @param status Exit status
 * @return Expanded string or NULL on error
 */
char	*process_expansion(char const *input, char **envp, int status)
{
	char	*res;
	int		i;
	int		last;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	last = 0;
	while (input[i])
	{
		if (is_variable_start(input, i))
		{
			if (process_var_expansion(&res, input, &i, &last) != 0
				|| expand_single_var(&res, input, &i, envp, status) != 0)
			{
				free(res);
				return (NULL);
			}
			last = i;
		}
		else
			i++;
	}
	return (finalize_expansion(res, input, last, i));
}

/**
 * @brief Checks if current position starts a variable
 * @param input Input string
 * @param i Current index
 * @return 1 if variable start, 0 otherwise
 */
int	is_variable_start(char const *input, int i)
{
	return (input[i] == '$' && input[i + 1]
		&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'
			|| input[i + 1] == '?'));
}

/**
 * @brief Processes text before variable
 * @param res Result string pointer
 * @param input Input string
 * @param i Current index pointer
 * @param last Last processed index pointer
 * @return 0 on success, 1 on error
 */
int	process_var_expansion(char **res, char const *input, int *i, int *last)
{
	if (*i > *last)
		return (append_text(res, input, *last, *i - *last));
	return (0);
}

/**
 * @brief Expands single variable and update result
 * @param res Result string pointer
 * @param input Input string
 * @param i Current index pointer
 * @param envp Environment variables
 * @param status Exit status
 * return 0 on success, 1 on error
 */
int	expand_single_var(char **res, char const *input, int *i,
		char **envp, int status)
{
	char	*name;
	int		ret;

	name = get_var_name(input, i);
	if (!name)
		return (1);
	ret = append_var(res, name, envp, status);
	free(name);
	return (ret);
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
