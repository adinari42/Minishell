/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:25:25 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 19:28:29 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *str)
{
	size_t	i;
	char	**split;

	i = 0;
	split = ft_split(str, ' ');
	while (split && split[0] && split[0][0]
		&& i < sizeof(g_builtins) / sizeof(const char *const))
	{
		if (!ft_strncmp(split[0], g_builtins[i], ft_strlen(g_builtins[i]) + 1))
		{
			free_split(split);
			return (i + 1);
		}
		i++;
	}
	if (split)
		free_split(split);
	return (0);
}
