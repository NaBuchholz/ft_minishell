/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:10:46 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/11/19 12:12:37 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_parse_format(const char *format, va_list ap)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i])
				total += ft_handle_type(format[i], ap);
		}
		else
		{
			write(1, &format[i], 1);
			total++;
		}
		i++;
	}
	return (total);
}
