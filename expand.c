/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:00:43 by slakner           #+#    #+#             */
/*   Updated: 2022/11/16 23:36:27 by adinari          ###   ########.fr       */
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
	while (tmp && (tmp != ft_strchr(tmp, ' ') || tmp != ft_strchr(tmp, '\0')))
	{
		printf("len = %d\n", len);
		len++;
		tmp++;
	}
	printf("len = %d\n", len);
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
	char 	*value;
	char	*tmp;
	t_token	*tmp1;

	tmp1 = list;
	while (tmp1)
	{
		if (tmp1->type != STR_SQUOTES)
		{
			tmp = tmp1->str;
			while (tmp)
			{	if (*tmp == '$')
				{
					value = value_expand(envp, tmp + 1);
					free(tmp1->str);
					tmp1->str = value;
				}
				tmp++;
			}
			tmp1 = tmp1->next;
		}
	}
}