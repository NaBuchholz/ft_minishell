/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 19:28:09 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/10/24 11:38:11 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	int	count;

	if (fd < 0 || s == NULL)
		return ;
	count = 0;
	while (s[count])
	{
		write(fd, &s[count], 1);
		count++;
	}
}
