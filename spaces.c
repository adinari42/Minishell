/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:05:25 by slakner           #+#    #+#             */
/*   Updated: 2022/11/25 12:41:48 by slakner          ###   ########.fr       */
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
	while (token && token->type == SPACE)
		token = token->next;
	return (token);
}
