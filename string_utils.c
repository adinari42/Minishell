/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:15:32 by slakner           #+#    #+#             */
/*   Updated: 2022/12/03 15:18:33 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free_str1(char *str1, char *str2)
{
	char	*tmp;
	char	*joined;

	tmp = str1;
	joined = ft_strjoin(str1, str2);
	free(tmp);
	return (joined);
}

int	count_split_elems(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i][0])
		i ++;
	return (i);
}
