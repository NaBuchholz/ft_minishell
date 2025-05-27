/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 03:02:08 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/17 03:26:06 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	temp;
	unsigned char	*temp_s;
	size_t			count;

	temp = (unsigned char)c;
	temp_s = (unsigned char *)s;
	count = 0;
	while (count < n)
	{
		if (temp == temp_s[count])
			return (temp_s + count);
		count++;
	}
	return (NULL);
}
