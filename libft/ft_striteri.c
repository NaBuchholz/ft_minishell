/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:14:09 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/23 17:29:17 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	len_s;
	unsigned int	count;

	len_s = ft_strlen(s);
	count = 0;
	while (count < len_s)
	{
		f(count, &s[count]);
		count++;
	}
}
