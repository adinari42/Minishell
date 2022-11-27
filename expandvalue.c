/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:18:59 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 22:28:45 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_expand(char **envp, char *var)
{
	int		j;
	char	*value;
	size_t	len;
	char	*tmp;

	len = 0;
	tmp = var;
	j = -1;
	while (envp[++j])
	{
		if (envp[j] && *(envp[j]) && !ft_strncmp(envp[j], var, ft_strlen(var)))
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



/********add necessary spaces*******/
char	*add_space(char *tmp, char *res)
{
	char	*tmp1;
	while (*tmp && *tmp == ' ')//add spaces
	{
		tmp1 = res;
		res = ft_strjoin(res, " ");
		free(tmp1);
		tmp++;
	}
	return (res);
}
char	*join_to_res(char *tmp, char **split2, char *res, int j, char **envp)
{
	char	*tmp1;

	if (j != 0  ||  (j == 0 && *tmp == '$'))
		split2[j] = value_expand(envp, split2[j]);
	tmp1 = res;
	res = ft_strjoin(res, split2[j]);
	free(tmp1);
	return (res);
}
/*
-split the token twice, once using spaces to seperate words,
-then split the words using $ to seperate variables from non variables,
-add spaces in the result at the beginning 
or after every word depending on the original format(tmp works as a reference)
-then check if the word starts with $ and expand it then join to to result
-skip the letters of the word in tmp and repeat
*/
char	*expand_value(char *str, char **envp)
{
	char		**split1;
	char		**split2;
	t_expand	counter;
	char		*res;
	char		*tmp;
	char 		*tmp1;

	counter.i = 0;
	counter.k = 0;
	split1 = ft_split(str, ' ');
	tmp = str;
	res = ft_strdup("");
	while (split1[counter.i])
	{
		counter.j = 0;
		split2 = ft_split(split1[counter.i], '$');//split using $
		while (split2[counter.j])
		{
			/********add necessary spaces*******/
			while (tmp[counter.k] && tmp[counter.k] == ' ')//add spaces
			{
				tmp1 = res;
				res = ft_strjoin(res, " ");
				free(tmp1);
				counter.k++;
			}
			/*******expand values*******/
			if (counter.j != 0  ||  (counter.j == 0 && tmp[counter.k] == '$'))
				split2[counter.j] = value_expand(envp, split2[counter.j]);
			tmp1 = res;
			res = ft_strjoin(res, split2[counter.j]);
			/*******reach end of word********/
			while (tmp[counter.k] && tmp[counter.k] != ' ')
			{
				counter.k++;
				if (tmp[counter.k + 1] == '$')
					break;
			}
			counter.j++;
		}
		free_2d(&split2);
		counter.i++;
	}
	free_strings(str, split1);
	return (res);
}

void	check_value(t_token *list, char **envp)
{
	t_token	*tmp1;
	char	*str_tmp;

	tmp1 = list;
	while (tmp1)
	{
		str_tmp = expand_value(tmp1->str, envp);
		tmp1->str = str_tmp;
		tmp1 = tmp1->next;
	}
}
