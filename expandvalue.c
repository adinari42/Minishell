/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvalue.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:18:59 by adinari           #+#    #+#             */
/*   Updated: 2022/12/30 23:08:41 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
-split the token twice, once using spaces to seperate words,
-then split the words using $ to seperate variables from non variables,
-add spaces in the result at the beginning 
or after every word depending on the original format(tmp works as a reference)
-then check if the word starts with $ and expand it then join to to result
-skip the letters of the word in tmp and repeat
*/
void	init_values(char *str, t_expand *counter, t_expval	*exp)
{
	counter->k = 0;
	exp->tmp = str;
	exp->res = ft_strdup("");
	counter->j = 0;
	exp->split2 = ft_split(str, '$');
}

void	set_value( t_expval exp, t_expand counter, t_dlist *env, t_pipe *data)
{
	exp.val = get_value_from_key(env, exp.split2[counter.j], data);
	if (exp.split2[counter.j])
		free(exp.split2[counter.j]);
	exp.split2[counter.j] = ft_strdup(exp.val);
	free(exp.val);
}

char	*expand_value(char *str, t_dlist *env, t_pipe *data)
{
	t_expand	counter;
	t_expval	exp;

	init_values(str, &counter, &exp);
	while (exp.split2[counter.j] && exp.split2[counter.j][0])
	{
		if (counter.j != 0 || (counter.j == 0 && exp.tmp[counter.k] == '$'))
			set_value(exp, counter, env, data);
		exp.res = ft_strjoin_free_str1(exp.res, exp.split2[counter.j]);
		while (exp.tmp[counter.k] && exp.tmp[counter.k] != ' ')
		{
			counter.k++;
			if (exp.tmp[counter.k + 1] == '$')
				break ;
		}
		counter.j++;
	}
	free_split(exp.split2);
	free(str);
	return (exp.res);
}

void	check_value(t_token *list, t_dlist *env, t_pipe *data)
{
	while (list)
	{
		if (list->type != STR_SQUOTES)
			list->str = expand_value(list->str, env, data);
		list = list->next;
	}
}
