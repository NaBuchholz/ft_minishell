/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:53:05 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/24 17:22:04 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest_str;

	dest_str = (char *)malloc(ft_strlen(s1) + 1);
	if (!dest_str)
		return (NULL);
	ft_strlcpy(dest_str, s1, ft_strlen(s1) + 1);
	return (dest_str);
}
