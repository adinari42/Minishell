/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:29:20 by adinari           #+#    #+#             */
/*   Updated: 2022/04/20 05:17:59 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_set;
	t_list	*index;

	if (!lst)
		return (NULL);
	index = lst;
	new_node = ft_lstnew(f(index->content));
	if (!new_node)
		return (NULL);
	index = index->next;
	while (index)
	{
		new_set = ft_lstnew(f(index->content));
		if (!new_set)
		{
			ft_lstclear(&new_node, del);
			return (NULL);
		}
		ft_lstadd_back(&new_node, new_set);
		index = index->next;
	}
	return (new_node);
}
