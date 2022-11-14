/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:49:16 by slakner           #+#    #+#             */
/*   Updated: 2022/11/14 22:19:06 by slakner          ###   ########.fr       */
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

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->str)
			free(token_str);
		free(token);
	}
}

void	delete(t_token **list, t_token *del_elem)
{
	t_token	*elem;
	t_token	*prev;
	t_token	*next;

	elem = *list;
	if (!elem)
	{
		free_token(del_elem);
		return ;
	}
	if (token->prev)
		token->prev->next = token->next;
	if (token->next)
		token->next->prev = token->prev;
	free_token(token);
}

void	append(t_token **list, t_token *new_elem)
{
	t_token	*last;

	if (!list || !new_elem)
		return ;
	if (!*list)
	{
		*list = new_elem;
		return ;
	}
	last = list_end(list);
	if (last)
	{
		last->next = new_elem;
		new_elem->prev = last;
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
