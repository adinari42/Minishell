/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:32:45 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 15:26:00 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **splitret)
{
	int	i;

	i = 0;
	while (splitret[i])
	{
		free(splitret[i]);
		i++;
	}
	free (splitret);
}

void	free_token_list(t_token **list)
{
	t_token	*elem;
	t_token	*next;

	if (!list)
		return ;
	elem = *list;
	while (elem)
	{
		next = elem->next;
		free_token(elem);
		elem = next;
	}
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

void	free_2d(char ***to_free)
{
	size_t	i;

	i = 0;
	if (*to_free == NULL)
		return ;
	while ((*to_free)[i] != NULL)
	{
		free((*to_free)[i]);
		++i;
	}
	free(*to_free);
	*to_free = NULL;
}

void	free_strings(char *str, char **split1)
{
	free(str);
	free_2d(&split1);
}

void	free_dlist(t_dlist *list)
{
	t_dlist	*elem;
	t_dlist	*tmp;

	elem = list;
	while (elem)
	{
		if (elem->content)
		{
			if (elem->content->key)
				free(elem->content->key);
			if (elem->content->val)
				free(elem->content->val);
			free(elem->content);
		}
		tmp = elem;
		elem = elem->next;
		free(tmp);
	}
}
