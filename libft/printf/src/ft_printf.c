/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 12:24:11 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/11/18 14:52:04 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		total;
	va_list	ap;

	if (!format)
		return (-1);
	total = 0;
	va_start(ap, format);
	total += ft_parse_format(format, ap);
	va_end(ap);
	return (total);
}
