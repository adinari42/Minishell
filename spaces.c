/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:05:25 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 21:26:07 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/******************************************************************************
** this function skips any spaces coming AFTER the argument "token"
** it should be called once 'token' has already been processed
** and returns the next non-space token
******************************************************************************/
t_token	*skip_spaces(t_token *token)
{
	token = token->next;
	while (token && token->type == SPACE_TKN)
		token = token->next;
	return (token);
}

t_token	*skip_empty(t_token *token)
{
	while (token && !token->str[0])
		token = token->next;
	return (token);
}

t_token	**tabs_to_spaces(t_token **pipes)
{
	int		i;
	t_token	*tkn;

	i = 0;
	while (pipes[i])
	{
		tkn = pipes[i];
		while (tkn)
		{
			if (tkn->type == SPACE_TKN)
				tkn->str[0] = ' ';
			tkn = tkn->next;
		}
		i++;
	}
	return (pipes);
}
