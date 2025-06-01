/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:40:02 by nbuchhol          #+#    #+#             */
/*   Updated: 2025/06/01 17:14:18 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_atoi(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	size_t	count;
	int		sign_aux;
	int		result;

	sign_aux = 1;
	count = 0;
	result = 0;
	while (ft_isspace_atoi(str[count]))
		count++;
	if (str[count] == 43 && str[count + 1] != 45)
		count++;
	if (str[count] == 45)
	{
		sign_aux *= -1;
		count++;
	}
	while (ft_isdigit(str[count]))
	{
		result *= 10;
		result += str[count] - 48;
		count++;
	}
	return (result *= sign_aux);
}
