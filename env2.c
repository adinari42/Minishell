/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:29:18 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 19:40:54 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	var_in_env(char *varname, t_dlist *env)
{
	t_dlist	*elem;

	elem = env;
	while (elem)
	{
		if (!ft_strncmp(varname, elem->content->key, ft_strlen(varname) + 1))
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	display_env(t_dlist *env)
{
	t_dlist	*var;

	var = env;
	while (var && var->content
		&& ft_strncmp(var->content->key, "?", 2))
	{
		printf("%s=", var->content->key);
		if (var->content->val)
			printf("%s", var->content->val);
		printf("\n");
		var = var->next;
	}
	return (0);
}

char	*gen_line_for_env_var(t_dlist *elem)
{
	char	*buf;

	if (elem->content && elem->content->key)
	{
		buf = ft_strjoin(elem->content->key, "=");
		if (elem->content->val && (elem->content->val)[0])
			return (ft_strjoin_free_str1(buf, elem->content->val));
		else
			return (ft_strdup(buf));
		free(buf);
	}
	else
		return (ft_strdup(""));
}

char	**env_list_to_char_arr(t_dlist **env)
{
	int		i;
	t_dlist	*elem;
	char	**env_c;

	if (!env || !*env)
		return (NULL);
	i = 0;
	elem = *env;
	env_c = malloc(sizeof(char *) * (lstsize(*env) + 1));
	if (!env_c)
		return (NULL);
	while (i < lstsize(*env))
	{
		env_c[i] = gen_line_for_env_var(elem);
		i++;
		elem = elem->next;
	}
	*(env_c + i) = NULL;
	return (env_c);
}
