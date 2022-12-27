/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 18:15:44 by slakner           #+#    #+#             */
/*   Updated: 2022/12/09 19:24:28 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lstsize(t_dlist *lst)
{
	int	cnt;

	if (!lst)
		return (0);
	cnt = 0;
	while (lst)
	{
		cnt ++;
		lst = lst->next;
	}
	return (cnt);
}

void	lstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*last;

	if (!new && !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = lstlast(*lst);
	if (last)
		last->next = new;
}

void	lstadd_front(t_dlist **lst, t_dlist *new)
{
	if (lst && new)
	{
		new->next = *lst;
		*lst = new;
	}	
}

t_dlist	*lstlast(t_dlist *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_dlist	*lstnew(t_kval *content)
{
	t_dlist	*newlist;

	newlist = malloc(sizeof(struct s_list));
	if (!newlist)
		return (NULL);
	newlist->content = content;
	newlist->next = NULL;
	return (newlist);
}

void	lstdel_elem(t_dlist **lst, t_dlist *elem)
{
	t_dlist	*cur;

	cur = *lst;
	if (cur == elem)
	{
		*lst = cur->next;
		if (cur->content)
			free_kval(cur->content);
		free(cur);
		return ;
	}
	while (cur)
	{
		if (cur->next && cur->next == elem)
		{	
			cur->next = elem->next;
			if (elem->content)
				free_kval(elem->content);
			free(elem);
			break ;
		}
		cur = cur->next;
	}
}
