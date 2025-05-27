/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:13:59 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/21 16:10:12 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t len)
{
	char		*dest;
	size_t		src_len;

	if (!src)
		return (NULL);
	src_len = ft_strlen(src);
	if (start >= src_len)
		return (ft_strdup(""));
	if (len > src_len - start)
		len = src_len - start;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src + start, len + 1);
	return (dest);
}
