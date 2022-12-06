/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltokens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:49:16 by slakner           #+#    #+#             */
/*   Updated: 2022/12/05 22:38:21 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *str)
{
	t_token		*newtoken;
	static int	idx;

	newtoken = malloc(sizeof(t_token));
	if (newtoken)
	{
		newtoken->str = ft_strdup(str);
		newtoken->type = token_type(str);
		newtoken->id = idx;
		newtoken->prev = NULL;
		newtoken->next = NULL;
	}
	idx ++;
	return (newtoken);
}

void	delete(t_token *elem)
{
	if (!elem)
		return ;
	if (elem->prev)
		elem->prev->next = elem->next;
	if (elem->next)
		elem->next->prev = elem->prev;
	free_token(elem);
}

void	tappend(t_token **list, t_token *new_elem)
{
	t_token	*last;

	if (!list || !new_elem)
		return ;
	if (!*list)
	{
		*list = new_elem;
		return ;
	}
	last = tlist_end(*list);
	if (last)
	{
		last->next = new_elem;
		new_elem->prev = last;
	}
}

t_token	*tlist_end(t_token *token)
{
	t_token	*elemptr;

	elemptr = NULL;
	if (token)
	{
		elemptr = token;
		while (elemptr && elemptr->next)
		{
			elemptr = elemptr->next;
		}
		return (elemptr);
	}
	return (NULL);
}

t_token	*tlist_start(t_token *token)
{
	while (token && token->prev)
		token = token->prev;
	return (token);
}

// t_token	*pop(t_token **token)
// {
// 	t_token	*old_top;

// 	old_top = NULL;
// 	if (token && *token)
// 	{
// 		old_top = token_top(token);
// 		if (old_top)
// 		{
// 			if (old_top->prev)
// 			{
// 				old_top->prev->next = NULL;
// 				old_top->next = NULL;
// 				old_top->prev = NULL;
// 			}
// 		}
// 	}
// 	if (*token == old_top)
// 		*token = NULL;
// 	return (old_top);
// }
