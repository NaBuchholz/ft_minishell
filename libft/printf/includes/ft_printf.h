/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 10:11:52 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/11/19 12:27:46 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int	ft_putchar(char c);
int	ft_putstr(const char *str);
int	ft_putnbr(const long n);
int	ft_putnbr_base(long num, int base);
int	ft_putnbr_base_uppercase(long num, int base);
int	ft_putptr(va_list ap);
int	ft_handle_type(const char type, va_list ap);
int	ft_parse_format(const char *format, va_list ap);
int	ft_printf(const char *format, ...);

#endif
