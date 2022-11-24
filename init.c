/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:14:00 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 15:32:21 by slakner          ###   ########.fr       */
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
	t_kval	*var;
	char	**tmp;

	i = 0;
	if (!envp)
		return (1);
	g_env = malloc(sizeof(t_dlist *));
	*g_env = NULL;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		var = malloc(sizeof(t_kval));
		var->key = ft_strdup(tmp[0]);
		var->val = ft_strdup(tmp[1]);
		free_split(tmp);
		lstadd_back(g_env, lstnew(var));
		i++;
	}
	return (0);
}
