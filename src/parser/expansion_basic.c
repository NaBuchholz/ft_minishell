/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_basic.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:01:53 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/16 20:33:42 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * @brief Appends text segment to result string
 * @param res Pointer to result string
 * @param input Input string
 * @param start Start index
 * @param len Length to copy
 * @return 0 on success, 1 on error
 */
int	append_text(char **res, char const *input, int start, int len)
{
	char	*seg;
	char	*tmp;

	if (len <= 0)
		return (0);
	seg = ft_substr(input, start, len);
	if (!seg)
		return (1);
	tmp = ft_strjoin(*res, seg);
	free(*res);
	free(seg);
	if (!tmp)
		return (1);
	*res = tmp;
	return (0);
}

/**
 * @brief Gets environment variable value
 * @param name Variable name
 * @param envp Environment variables
 * @return Variable value or empty string if not found
 */
char	*get_env_value(char const *name, char **envp)
{
	size_t	nl;
	int		j;

	nl = ft_strlen(name);
	j = 0;
	while (envp[j])
	{
		if (ft_strncmp(envp[j], name, nl) == 0 && envp[j][nl] == '=')
			return (ft_strdup(envp[j] + nl + 1));
		j++;
	}
	return (ft_strdup(""));
}

/**
 * @brief Appends variable value to result string
 * @param res Pointer to result string
 * @param name Variable name
 * @param ctx Expansion context
 * @return 0 on success, 1 on error
 */
int	append_var(char **res, char const *name, t_exp_ctx *ctx)
{
	char	*val;
	char	*tmp;

	if (ft_strncmp(name, "?", 2) == 0)
		val = ft_itoa(ctx->exit_status);
	else
		val = get_env_value(name, ctx->envp);
	if (!val)
		return (1);
	tmp = ft_strjoin(*res, val);
	free(*res);
	free(val);
	if (!tmp)
		return (1);
	*res = tmp;
	return (0);
}

/**
 * @brief Extracts variable name from input string
 * @param input Input string
 * @param i Pointer to current index
 * @return Variable name string or NULL on error
 */
char	*get_var_name(char const *input, int *i)
{
	int	start;

	(*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	return (ft_substr(input, start, *i - start));
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
