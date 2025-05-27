/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:24:53 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/11/19 13:50:43 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr_base(long num, int base)
{
	size_t			count;
	char			*base_digits;
	unsigned long	unsigned_num;

	if (base < 2 || base > 16)
		return (0);
	count = 0;
	base_digits = "0123456789abcdef";
	if (num < 0)
	{
		if (base == 10)
			count += ft_putchar('-');
		unsigned_num = (unsigned long)num;
	}
	else
		unsigned_num = (unsigned long)num;
	if (unsigned_num >= (unsigned long)base)
		count += ft_putnbr_base(unsigned_num / base, base);
	count += ft_putchar(base_digits[unsigned_num % base]);
	return (count);
}
