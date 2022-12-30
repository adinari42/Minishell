/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:38:34 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 23:20:40 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(t_token **pipes)
{
	int		i;

	i = 0;
	while (pipes[i])
		i ++;
	return (i);
}

int	count_tokens(t_token *tokens, int tokentype)
{
	int	cnt;

	cnt = 1;
	while (tokens)
	{
		if (tokens->type == tokentype)
			cnt++;
		tokens = tokens->next;
	}
	return (cnt);
}

t_token	*cut_at_pipe(t_token *list, t_token **pipes, int i)
{
	t_token	*end;
	t_token	*next;

	end = list;
	next = NULL;
	pipes[i] = tlist_start(end);
	if (end->next)
	{
		next = end->next;
		next->prev = NULL;
	}
	if (end->prev)
		end->prev->next = NULL;
	free_token(end);
	return (next);
}

t_token	**list_to_pipes(t_token **list)
{
	t_token	**pipes;
	int		i;
	int		numpipes;
	t_token	*elem;

	if (!list)
		return (NULL);
	else if (!*list)
	{
		free(list);
		return (NULL);
	}
	numpipes = count_tokens(*list, PIPE);
	pipes = malloc(sizeof(t_token *) * (numpipes + 1));
	i = 0;
	elem = *list;
	pipes[0] = elem;
	while (elem->next)
	{
		if (elem->type == PIPE)
			elem = cut_at_pipe(elem, pipes, i++);
		else
			elem = elem->next;
	}
	free(list);
	pipes[numpipes - 1] = tlist_start(elem);
	pipes[numpipes] = NULL;
	return (pipes);
}
