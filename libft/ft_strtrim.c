/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 10:28:52 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/22 11:25:21 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimmed;
	size_t	i_start;
	size_t	i_finish;
	size_t	new_len;

	if (!s1)
		return (NULL);
	i_start = 0;
	i_finish = ft_strlen(s1) - 1;
	while (s1[i_start] && ft_strchr(set, s1[i_start]))
		i_start++;
	while (i_finish > i_start && ft_strchr(set, s1[i_finish]))
		i_finish--;
	new_len = i_finish - i_start + 1;
	str_trimmed = (char *)malloc(new_len + 1);
	if (!str_trimmed)
		return (NULL);
	ft_strlcpy(str_trimmed, &s1[i_start], new_len + 1);
	return (str_trimmed);
}
