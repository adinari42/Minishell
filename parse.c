/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:08:29 by slakner           #+#    #+#             */
/*   Updated: 2022/12/15 19:08:06 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_inpt(char *inpt)
{
	char	*start = inpt;

t_token	*remove_spaces(t_token *list)
{
	t_token	*token;

	token = tlist_start(list);
	while (token)
	{
		if (token->type == SPACE_TKN)
			delete(token);
		token = token->next;
	}
	return (list);
}

t_token	**remove_empty(t_token **list)
{
	t_token	*token;

	token = tlist_start(*list);
	while (token)
	{
		if (!ft_strlen(token->str))
			delete(token);
		token = token->next;
	}
	return (list);
}
