/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:01:13 by slakner           #+#    #+#             */
/*   Updated: 2022/12/19 22:46:45 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	**merge_quoted_strings(t_token **list, t_pipe *data)
{
	t_token	*token;
	t_token	*open_quote;

	token = tlist_start(list);
	open_quote = NULL;
	while (token)
	{
		if (token->type == SINGLE_QUOTE || token->type == DOUBLE_QUOTE)
		{
			open_quote = token;
			while (token && (open_quote == token
					|| open_quote->type != token->type))
			{
				if (!token->next)
				{
					ms_fd_error(258, data);
					data->error_code = 258;			// child process can't pass data back to the parent process without a pipe()
					free_token_list(*list);
					free(list);
					return (NULL);
				}
				token = token->next;
			}
			token = merge_tokens(open_quote, token);
		}
		token = token->next;
	}
	return (list);
}

t_token	*merge_tokens(t_token *first, t_token *last)
{
	char	*tstr;

	if (first == last)
		return (first);
	while (first->next != last)
		first = merge_two_tokens(first, first->next);
	first = merge_two_tokens(first, first->next);
	if (first->type == DOUBLE_QUOTE)
		first->type = STR_DQUOTES;
	else if (first->type == SINGLE_QUOTE)
		first->type = STR_SQUOTES;
	tstr = ft_substr(first->str, 1, ft_strlen(first->str) - 2);
	free (first->str);
	first->str = tstr;
	return (first);
}

t_token	*merge_two_tokens(t_token *token1, t_token *token2)
{
	char	*newstr;

	if (token1 == token2)
		return (token1);
	newstr = ft_strjoin(token1->str, token2->str);
	free(token1->str);
	free(token2->str);
	token1->str = newstr;
	token1->next = token2->next;
	if (token1->next)
		token1->next->prev = token1;
	free(token2);
	return (token1);
}
