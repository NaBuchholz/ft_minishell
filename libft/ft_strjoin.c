/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:28:38 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/21 18:13:26 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *prefix_str, char const *sulffix_str)
{
	char	*new_str;
	size_t	sulffix_len;
	size_t	prefix_len;

	prefix_len = ft_strlen(prefix_str);
	sulffix_len = ft_strlen(sulffix_str);
	new_str = (char *) malloc((prefix_len + sulffix_len + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, prefix_str, prefix_len + 1);
	ft_strlcat(new_str, sulffix_str, prefix_len + sulffix_len + 1);
	return (new_str);
}
