/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:00:43 by slakner           #+#    #+#             */
/*   Updated: 2022/11/18 15:53:50 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_expand(char **envp, char *var)
{
	int		j;
	char	*value;
	int		len;
	char	*tmp;
	
	// len = ft_strlen(var);
	len = 0;

	tmp = var;
	// while (tmp && (tmp != ft_strchr(tmp, ' ') || tmp != ft_strchr(tmp, '\0')))
	// {
	// 	printf("len = %d\n", len);
	// 	len++;
	// 	tmp++;
	// }
	// printf("len = %d\n", len);
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], var, len))
		{
			len += 1;
			break ;
		}
	}
	if (len != ft_strlen(var))
	{
		value = ft_strdup(*(envp + j) + len);
		return (value);
	}
	return (ft_strdup(""));
}

void	check_value(t_token *list, char **envp)
{
	char	**split1;
	char	**split2;
	char	*value;
	char	*tmp;
	t_token	*list_tmp;
	int		len;

	printf("len check %c\n", envp[1][1]);
	list_tmp = list;
	value = ft_strdup("");
	while (list_tmp)//1 : iterate through token nodes
	{
		//split using space


		//split individual onnes using $ sign




		list_tmp = list_tmp->next;//1
	}
}
// while (split2[j])
// 		{
// 			/********add necessary spaces*******/
// 			while (tmp[k] && tmp[k] == ' ')//add spaces
// 			{
// 				tmp1 = res;
// 				res = ft_strjoin(res, " ");
// 				free(tmp1);
// 				k++;
// 			}
// 			/*******expand values*******/
// 			if (j != 0  ||  (j == 0 && tmp[k] == '$'))
// 				split2[j] = value_expand(envp, split2[j]);
// 			tmp1 = res;
// 			res = ft_strjoin(res, split2[j]);
// 			free(tmp1);
// 			/*******reach end of word********/
// 			while (tmp[k] && tmp[k] != ' ')
// 			{
// 				k++;
// 				if (tmp[k + 1] == '$')
// 					break;
// 			}
// 			j++;
// 		}