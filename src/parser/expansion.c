/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:01 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/15 22:24:13 by vinda-si         ###   ########.fr       */
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
static int	append_text(char **res, char const *input, int start, int len)
{
	char	*seg;
	char	*tmp;

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
static char	*get_env_value(char const *name, char **envp)
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
 * @param envp Enviroment variables
 * @param status Exit status for $?
 * @return 0 on success, 1 on error
 */
static int	append_var(char **res, char const *name,
		char **envp, int status)
{
	char	*val;
	char	*tmp;

	if (ft_strncmp(name, "?", 2) == 0)
		val = ft_itoa(status);
	else
		val = get_env_value(name, envp);
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
static char	*get_var_name(char const *input, int *i)
{
	int		start;

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
 * @brief Expands all variables in input string
 * @param input Input string with variables
 * @param envp Environment variables
 * @param status Exit status for $?
 * @return Expanded string or NULL on error
 */
char	*expand_variables(char const *input, char **envp, int status)
{
	return (process_expansion(input, envp, status));
}
