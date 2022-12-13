/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:38:34 by slakner           #+#    #+#             */
/*   Updated: 2022/12/08 18:05:10 by slakner          ###   ########.fr       */
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

// we might have to make a copy of the original list with memcopy since it gets changed here
// assign i+1 and mark end of array somehow?
t_token	**list_to_pipes(t_token **list)
{
	t_token	**pipes;
	int		i;
	int		numpipes;
	t_token	*elem;

	numpipes = count_tokens(list, PIPE);
	pipes = malloc(sizeof(t_token *) * (numpipes + 1));
	i = 0;
	if (!list)
		return (NULL);
	if (list->type == PIPE)
		prnt_err("", "", "syntax error near unexpected token `|'");
	pipes[0] = list;
	while (list->next)
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
