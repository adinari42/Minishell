/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:38:34 by slakner           #+#    #+#             */
/*   Updated: 2022/12/19 21:07:51 by slakner          ###   ########.fr       */
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
	free(end);
	return (next);
}

// we might have to make a copy of the original list with memcopy since it gets changed here
// assign i+1 and mark end of array somehow?
t_token	**list_to_pipes(t_token *list)
{
	t_token	**pipes;
	int		i;
	int		numpipes;

	numpipes = count_tokens(list, PIPE);
	pipes = malloc(sizeof(t_token *) * (numpipes + 1));
	i = 0;
	if (!list)
		return (NULL);
	pipes[0] = elem;
	while (elem->next)
	{
		if (list->type == PIPE)
		{
			list = cut_at_pipe(list, pipes, i);
			i++;
		}
		else
			list = list->next;
	}
	pipes[numpipes - 1] = tlist_start(list);
	pipes[numpipes] = NULL;
	return (pipes);
}
