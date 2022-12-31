/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:32:45 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:29:49 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **splitret)
{
	int	i;

	if (!splitret)
		return ;
	i = 0;
	while (splitret[i] && ft_strncmp(splitret[i], "", 1))
	{
		free(splitret[i]);
		i++;
	}
	free(splitret[i]);
	free(splitret);
	return ;
}

void	free_token_list(t_token *list)
{
	t_token	*elem;
	t_token	*next;

	if (!list)
		return ;
	elem = list;
	while (elem && elem->str)
	{
		next = elem->next;
		free_token(elem);
		elem = next;
	}
	free_token(elem);
}

void	free_token_list_and_ptr(t_token **list)
{
	t_token	*elem;
	t_token	*next;

	if (!list)
		return ;
	elem = *list;
	while (elem && elem->str)
	{
		next = elem->next;
		free_token(elem);
		elem = next;
	}
	free_token(elem);
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

void	free_parse(t_parse *parse)
{
	if (parse->path)
		free(parse->path);
	free_char_arr(parse->cmd);
}
