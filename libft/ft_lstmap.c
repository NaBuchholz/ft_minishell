/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuchhol <nbuchhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:28:08 by nbuchhol          #+#    #+#             */
/*   Updated: 2024/12/18 15:28:24 by nbuchhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void*), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current_content;
	void	*new_content;
	t_list	*new_node;

	new_list = NULL;
	current_content = lst;
	while (current_content)
	{
		new_content = f(current_content->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		current_content = current_content->next;
	}
	return (new_list);
}
