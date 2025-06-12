/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinda-si <vinda-si@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 19:33:01 by vinda-si          #+#    #+#             */
/*   Updated: 2025/06/11 22:24:26 by vinda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static int	append_var(char **res, char const *name,
		char **envp, int status)
{
	char	*val;
	char	*tmp;
	int		j;
	size_t	nl;

	if (ft_strncmp(name, "?", 2) == 0)
		val = ft_itoa(status);
	else
	{
		nl = ft_strlen(name);
		j = 0;
		val = NULL;
		while (envp[j])
		{
			if (ft_strncmp(envp[j], name, nl) == 0
				&& envp[j][nl] == '=')
			{
				val = ft_strdup(envp[j] + nl + 1);
				break;
			}
			j++;
		}
		if (!val)
			val = ft_strdup("");
	}
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
static char	*get_var_name(char const *input, int *i)
{
	int		start;
	char	*name;

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

char	*expand_variables(char const *input, char **envp, int status)
{
	char	*res;
	char	*name;
	int		i;
	int		last;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	last = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1]
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'
				|| input[i + 1] == '?'))
		{
			if (i > last && append_text(&res, input, last, i - last))
			{
				free(res);
				return (NULL);
			}
			name = get_var_name(input, &i);
			if (!name || append_var(&res, name, envp, status))
			{
				free(name);
				free(res);
				return (NULL);
			}
			free(name);
			last = i;
		}
		else
			i++;
	}
	if (last < i && append_text(&res, input, last, i - last))
	{
		free(res);
		return (NULL);
	}
	return (res);
}
