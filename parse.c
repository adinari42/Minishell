/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:08:29 by slakner           #+#    #+#             */
/*   Updated: 2022/12/19 21:03:09 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// we actually need to process the information for some of the spaces
// echo "foo"
// is different from 
// echo"foo"
// and 
// echo "foo" "bar"
// is different from 
// echo "foo""bar"


int	is_empty_inpt(char *inpt)
{
	char	*start = inpt;

	if (!inpt)
		return (1);
	while (is_whitespace(inpt))
		inpt ++;
	if (!*inpt)
	{
		free(start);
		return (1);
	}
	return (0);
}

//checks if there is a string before the first pipe, between two pipes, and behind the last pipe
int	check_pipes(t_token *tkn)
{
	int	expect_cmd;

	expect_cmd = 258;
	while (tkn)
	{
		while (tkn->type == SPACE_TKN)
			tkn = tkn->next;
		if (tkn->type == WORD || tkn->type == STR_DQUOTES || tkn->type == STR_SQUOTES)
			expect_cmd = 0;
		else if (tkn->type == PIPE && expect_cmd)
		{
			printf("Minishell: syntax error near unexpected token `|'\n");
			return (258);
		}
		else if (tkn->type == PIPE)
			expect_cmd = 258;
		tkn = tkn->next;
	}
	return (expect_cmd);
}

int	parse(t_token *list, t_pipe *data)
{
	int	ret;

	ret = 0;
	while (list->type == SPACE_TKN)
		list = list->next;
	if (!list)
		return (ret);
	data->error_code += check_pipes(list);
	return (data->error_code);
}

t_token	*remove_spaces(t_token *list)
{
	t_token	*token;

	token = tlist_start(list);
	while (token)
	{
		if (token->type == SPACE)
			delete(token);
		token = token->next;
	}
	return (list);
}

t_token	**remove_empty(t_token **list)
{
	t_token	*token;

	token = tlist_start(list);
	while (token)
	{
		if (!ft_strlen(token->str))
			delete(token);
		token = token->next;
	}
	return (list);
}
