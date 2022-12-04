/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:18:59 by adinari           #+#    #+#             */
/*   Updated: 2022/12/04 15:41:49 by slakner          ###   ########.fr       */
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
	j = 0;
	while (envp[j] && envp[j][0])// && ft_strncmp(envp[j], "", 1))
	{
		if (envp[j] && *(envp[j]) && !ft_strncmp(envp[j], var, ft_strlen(var)))
		{
			len += ft_strlen(var);
			break ;
		}
		j++;
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
// char	*add_space(char *tmp, char *res)
// {
// 	while (*tmp && *tmp == ' ') //add spaces
// 	{
// 		res = ft_strjoin_free_str1(res, " ");
// 		tmp++;
// 	}
// 	return (res);
// }

char	*join_to_res(char *tmp, char **split2, char *res, int j, char **envp)
{
	if (j != 0 || (j == 0 && *tmp == '$'))
		split2[j] = value_expand(envp, split2[j]);
	res = ft_strjoin_free_str1(res, split2[j]);
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
char	*expand_value(char *str)
{
	char		**split1;
	char		**split2;
	t_expand	counter;
	char		*res;
	char		*tmp;
	char		*val;

	counter.i = 0;
	counter.k = 0;
	split1 = ft_split(str, ' ');
	tmp = str;
	res = ft_strdup("");
	while (split1[counter.i])
	{
		counter.j = 0;
		split2 = ft_split(split1[counter.i], '$'); //split using $
		while (split2[counter.j])
		{
			/********add necessary spaces*******/
			while (tmp[counter.k] && tmp[counter.k] == ' ')//add spaces
			{
				res = ft_strjoin_free_str1(res, " ");
				counter.k++;
			}
		// 	/*******expand values*******/
			if (counter.j != 0  ||  (counter.j == 0 && tmp[counter.k] == '$'))
				//split2[counter.j] = value_expand(envp, split2[counter.j]);
			{
				val = get_value_from_key(*g_env, split2[counter.j]);
				// if (val)
					split2[counter.j] = ft_strdup(get_value_from_key(*g_env, split2[counter.j]));
				// else
				// 	split2[counter.j] = ft_strdup("");
				// split2[counter.j] = ft_strdup(get_value_from_key(*g_env, split2[counter.j]));
			}
			res = ft_strjoin_free_str1(res, split2[counter.j]);
		// 	/*******reach end of word********/
			while (tmp[counter.k] && tmp[counter.k] != ' ')
			{
				counter.k++;
				if (tmp[counter.k + 1] == '$')
					break ;
			}
			counter.j++;
		}
		free_split(split2);
		counter.i++;
	}
	free_strings(str, split1);
	return (res);
}

void	check_value(t_token *list)
{
	t_token	*tmp1;
	char	*str_tmp;

	// (void) envp;
	// (void) list;
	tmp1 = list;
	while (tmp1)
	{
		str_tmp = expand_value(tmp1->str);
		tmp1->str = str_tmp;
		tmp1 = tmp1->next;
	}
}
