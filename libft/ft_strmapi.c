/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:37:17 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/23 13:09:45 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	len_s;
	unsigned int	count;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	new_str = (char *)ft_calloc(len_s + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	count = 0;
	while (count < len_s)
	{
		new_str[count] = f(count, s[count]);
		count++;
	}
	new_str[++count] = '\0';
	return (new_str);
}
