/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:35:00 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/15 20:04:12 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*temp_pt;

	temp_pt = (unsigned char *)s;
	while (len > 0)
	{
		*temp_pt = (unsigned char) c;
		temp_pt++;
		len--;
	}
	return (s);
}
