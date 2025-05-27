/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:10:55 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/11/19 12:28:27 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_handle_type(const char type, va_list ap)
{
	int	count;

	count = 0;
	if (type == 'c')
		count += ft_putchar(va_arg(ap, int));
	else if (type == 's')
		count += ft_putstr(va_arg(ap, char *));
	else if (type == 'p')
		count += ft_putptr(ap);
	else if (type == 'i' || type == 'd')
		count += ft_putnbr(va_arg(ap, int));
	else if (type == '%')
		count += ft_putchar('%');
	else if (type == 'u')
		count += ft_putnbr_base(va_arg(ap, unsigned int), 10);
	else if (type == 'x')
		count += ft_putnbr_base(va_arg(ap, unsigned int), 16);
	else if (type == 'X')
		count += ft_putnbr_base_uppercase(va_arg(ap, unsigned int), 16);
	return (count);
}
