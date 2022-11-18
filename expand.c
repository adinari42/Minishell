/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:00:43 by slakner           #+#    #+#             */
/*   Updated: 2022/11/17 19:58:36 by adinari          ###   ########.fr       */
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