/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:32:45 by slakner           #+#    #+#             */
/*   Updated: 2022/12/02 23:03:47 by slakner          ###   ########.fr       */
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

void	free_token_list(t_token *list)
{
	t_token	*elem;
	t_token	*next;

	if (!list)
		return ;
	elem = *list;
	while (elem && elem->str && ft_strncmp(elem->str, "", 1))
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
	free(parse->path);
	free_char_arr(parse->cmd);
}

void	free_char_arr(char **to_free)
{
	size_t	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i] != NULL) //&& *(to_free[i]) != '\0')
	{
		free(to_free[i]);
		++i;
	}
	free(to_free);
	to_free = NULL;
}

void	free_2d(char ***to_free)
{
	size_t	i;

	i = 0;
	if (!to_free || !(*to_free))
		return ;
	while (*(to_free)[i] && ft_strncmp(*(to_free)[i], "", 1))
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
