/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:25:12 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/16 21:36:33 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		count;

	count = 0;
	while (s[count])
	{
		if (s[count] == (char) c)
			return ((char *)s + count);
		count++;
	}
	if ((char)c == '\0')
		return ((char *)s + count);
	return (NULL);
}
