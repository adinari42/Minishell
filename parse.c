/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:08:29 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 18:18:57 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// we actually need to process the information for some of the spaces
// echo "foo"
// is different from 
// echo"foo"
// and 
// echo "foo" "bar"
// is different from 
// echo "foo""bar"

t_token	**remove_spaces(t_token **list)
{
	t_token	*token;

	token = tlist_start(list);
	while (token)
	{
		if (token->type == SPACE)
			delete(token);
		token = token->next;
	}
	return (list);
}

t_token	**remove_empty(t_token **list)
{
	t_token	*token;

	token = tlist_start(list);
	while (token)
	{
		if (!ft_strlen(token->str))
			delete(token);
		token = token->next;
	}
	return (list);
}
