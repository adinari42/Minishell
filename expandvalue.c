/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:18:59 by adinari           #+#    #+#             */
/*   Updated: 2022/12/03 15:35:38 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_expand(char **envp, char *var)
{
	int		j;
	char	*value;
	int		len;
	char	*tmp;

	len = 0;
	tmp = var;
	j = -1;
	while (envp[++j])
	{
		//if (envp[j] && *(envp[j]) && !ft_strncmp(envp[j], var, ft_strlen(var)))
		if (envp[j] && *(envp[j]))
		{
			len += ft_strlen(var);
			break ;
		}
	}
	// printf("couldnt find env variable, j = %d, len = %d\n", j, len);
	if (len == ft_strlen(var))
	{
		len += 1;
		value = ft_strdup(*(envp + j) + len);
		free(var);
		// printf("returning value str j = %d, len = %d\n", j, len);
		return (value);
	}
	free(var);
	// printf("returning empty str j = %d, len = %d\n", j, len);
	return (ft_strdup(""));
}



char	*expand_value(char *str, char **envp)
{
	char		**split1;
	char		**split2;
	t_expand	counter;
	char		*res;
	char		*tmp;

	i = 0;
	k = 0;
	split1 = ft_split(str, ' ');
	tmp = str;
	res = ft_strdup("");
	while (split1[i])
	{
		j = 0;
		split2 = ft_split(split1[i], '$');//split using $
		while (split2[j])
		{
			/********add necessary spaces*******/
			while (tmp[k] && tmp[k] == ' ')//add spaces
			{
				res = ft_strjoin_free_str1(res, " ");
				counter.k++;
			}
		// 	/*******expand values*******/
			if (counter.j != 0  ||  (counter.j == 0 && tmp[counter.k] == '$'))
				split2[counter.j] = value_expand(envp, split2[counter.j]);
			res = ft_strjoin_free_str1(res, split2[counter.j]);
		// 	/*******reach end of word********/
			while (tmp[counter.k] && tmp[counter.k] != ' ')
			{
				k++;
				if (tmp[k + 1] == '$')
					break;
			}
			j++;
		}
		free_2d(&split2);
		i++;
	}
	free_strings(str, split1);
	return (res);
}

void	check_value(t_token *list, char **envp)
{
	t_token	*tmp1;
	char	*str_tmp;

	// (void) envp;
	// str_tmp = NULL;
	tmp1 = list;
	while (tmp1)
	{
		str_tmp = expand_value(tmp1->str, envp);
		// free(tmp1->str);
		tmp1->str = str_tmp;
		tmp1 = tmp1->next;
	}
}
