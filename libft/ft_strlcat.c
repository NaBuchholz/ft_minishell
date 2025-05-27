/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:46:56 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/21 15:08:10 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	remaining_size;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= size)
		return (size + len_src);
	remaining_size = size - len_dst - 1;
	if (len_src < remaining_size)
	{
		ft_memcpy(dst + len_dst, src, len_src);
		dst[len_dst + len_src] = '\0';
	}
	else
	{
		ft_memcpy(dst + len_dst, src, remaining_size);
		dst[len_dst + remaining_size] = '\0';
	}
	return (len_dst + len_src);
}
