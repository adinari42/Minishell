/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:15:32 by slakner           #+#    #+#             */
/*   Updated: 2022/12/29 18:15:31 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(const char *c)
{
	if (*c == ' ' || *c == '\n' || *c == '\t'
		|| *c == '\v' || *c == '\f' || *c == '\r')
		return (1);
	else
		return (0);
}

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
// void	print_double_ptr(char **ptr)
// {
// 	int	f;

// 	f = 0;
// 	while (ptr[f])
// 	{
// 		printf("ptr[%d] = %s.\n",f, ptr[f]);
// 		f++;
// 	}
// }