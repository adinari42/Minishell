/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:14:00 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 18:50:04 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	init_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 		i++;
// 	g_envp = calloc(i * sizeof(char *));
// 	i = 0;
// 	while (envp[i])
// 		g_envp[i] = ft_strdup(envp[i]);
// }

int	init_env_llist(char **envp)
{
	int		i;
	t_dlist	*elem;
	t_kval	*var;
	char	**tmp;

	i = 0;
	var = malloc(sizeof(t_kval));
	if (!envp)
		return (1);
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		var->key = tmp[0];
		var->val = tmp[1];
		free_split(tmp);
		elem = lstnew((void *) var);
		if (!g_env)
			g_env = &elem;
		else
			lstadd_back(g_env, elem);
	}
	return (0);
}