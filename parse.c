/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:08:29 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 18:18:57 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	expect_cmd = 1;
	while (tkn)
	{
		while (tkn && tkn->type == SPACE_TKN)
			tkn = tkn->next;
		if (!tkn)
			break ;
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

int	check_quotes(t_token *tkn)
{
	int	quote_type;

	while (tkn)
	{
		if (tkn->type == DOUBLE_QUOTE || tkn->type == SINGLE_QUOTE)
		{
			quote_type = tkn->type;
			tkn = tkn->next;
			while (tkn && tkn->type != quote_type)
				tkn = tkn->next;
			if (!tkn || tkn->type != quote_type)
			{
				printf("Minishell: syntax error: unclosed quotes\n");
				return (258);
			}
		}
		tkn = tkn->next;
	}
	return (0);
}

int	parse(t_token **list, t_pipe *data)
{
	int	ret;

	ret = check_quotes(*list);
	if (ret)
	{
		data->error_code = ret;
		return (ret);
	}
	merge_quoted_strings(list);
	ret = check_pipes(*list);
	if (ret)
		data->error_code = ret;
	return (ret);
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
