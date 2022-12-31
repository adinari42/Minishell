/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 00:30:16 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 01:01:08 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_char_arr(char **to_free)
{
	size_t	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i] && ft_strncmp(to_free[i], "", 1))
	{
		free(to_free[i]);
		++i;
	}
	free(to_free[i]);
	free(to_free);
}

void	free_dlist(t_dlist *list)
{
	t_dlist	*elem;
	t_dlist	*tmp;

	elem = list;
	while (elem)
	{
		if (elem->content)
			free_kval(elem->content);
		tmp = elem;
		elem = elem->next;
		free(tmp);
	}
}

void	free_kval(t_kval *kval)
{
	if (kval)
	{
		if (kval->key)
			free(kval->key);
		if (kval->val)
			free(kval->val);
		free(kval);
	}
}

void	free_pipes(t_token **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (pipes && pipes[i])
	{
		free_token_list(pipes[i]);
		i ++;
	}
	free(pipes[i]);
	if (pipes)
		free(pipes);
}

void	free_if_non_null(char *str)
{
	if (str)
		free(str);
}
