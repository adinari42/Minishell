/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:49:16 by slakner           #+#    #+#             */
/*   Updated: 2022/11/14 22:49:47 by slakner          ###   ########.fr       */
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
		newtoken->str = str;
		newtoken->type = token_type(str);
		newtoken->id = idx;
		newtoken->prev = NULL;
		newtoken->next = NULL;
	}
	idx ++;
	return (newtoken);
}

void	free_token_list(t_token **list)
{
	t_token	*elem;
	t_token	*next;

	if (!list)
		return ;
	elem = *list;
	while (elem)
	{
		next = elem->next;
		free_token(elem);
		elem = next;
	}
	free(list);
}

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token->str);
		free(token);
	}
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

void	append(t_token **list, t_token *new_elem)
{
	t_token	*last;

	if (!list || !new_elem)
		return ;
	if (!*list)
	{
		top->next = new_elem;
		new_elem->prev = top;
	}
}

t_token	*list_end(t_token **token)
{
	t_token	*elemptr;

	elemptr = NULL;
	if (token && *token)
	{
		elemptr = *token;
		while (elemptr && elemptr->next)
		{
			elemptr = elemptr->next;
		}
		return (elemptr);
	}
	return (NULL);
}

t_token	*list_start(t_token **token)
{
	if (token && *token)
		return (*token);
	return (NULL);
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
