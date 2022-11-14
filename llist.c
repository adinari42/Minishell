/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:49:16 by slakner           #+#    #+#             */
/*   Updated: 2022/11/14 20:25:29 by slakner          ###   ########.fr       */
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

void	append(t_token **token, t_token *new_elem)
{
	t_token	*top;

	if (!token || !new_elem)
		return ;
	if (!*token)
	{
		*token = new_elem;
		return ;
	}
	top = list_end(token);
	if (top)
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
