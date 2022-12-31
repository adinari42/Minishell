/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:39:48 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 01:19:52 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens.h"

int	token_type(char *c)
{
	if (!ft_strncmp(c, "<<", 2))
		return (APPEND_IN);
	else if (!ft_strncmp(c, ">>", 2))
		return (APPEND_OUT);
	else if (!ft_strncmp(c, "<", 1))
		return (REDIR_IN);
	else if (!ft_strncmp(c, ">", 1))
		return (REDIR_OUT);
	else if (!ft_strncmp(c, "\"", 1))
		return (DOUBLE_QUOTE);
	else if (!ft_strncmp(c, "'", 1))
		return (SINGLE_QUOTE);
	else if (!ft_strncmp(c, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(c, " ", 1) || !ft_strncmp(c, "\t", 1))
		return (SPACE_TKN);
	else if (!ft_strncmp(c, "=", 1))
		return (ASSIGN);
	else
		return (WORD);
}

char	*non_word_tknstr(char *bashcmd, size_t *i)
{
	char	*tokenstr;

	if (*i < ft_strlen(bashcmd) - 1
		&& bashcmd[*i] == '<' && bashcmd[(*i) + 1] == '<' && ++(*i))
		tokenstr = ft_strdup("<<");
	else if (*i < ft_strlen(bashcmd) - 1
		&& bashcmd[*i] == '>' && bashcmd[(*i) + 1] == '>' && ++(*i))
		tokenstr = ft_strdup(">>");
	else
		tokenstr = ft_substr(bashcmd, *i, 1);
	return (tokenstr);
}

t_token	**read_tokens(char *cmd)
{
	const char	spec_c[] = "\"'<>| =\t";
	t_token		**tk_list;
	size_t		word_s;
	size_t		i;

	tk_list = malloc(sizeof(t_token *));
	*tk_list = NULL;
	i = 0;
	while (i < ft_strlen(cmd) && (cmd[i] == ' ' || cmd[i] == '\t'))
		i++;
	word_s = i;
	while (i < ft_strlen(cmd))
	{
		if (char_in_charset(cmd[i], spec_c))
		{
			if (i - word_s > 0)
				append_from_str(tk_list, ft_substr(cmd, word_s, i - word_s));
			append_from_str(tk_list, non_word_tknstr(cmd, &i));
			word_s = i + 1;
		}
		i++;
	}
	if (word_s < i)
		append_from_str(tk_list, ft_substr(cmd, word_s, i - word_s));
	return (tk_list);
}

t_token	**tokenize(char *cmd)
{
	t_token	**ltokens;

	ltokens = read_tokens(cmd);
	ltokens = merge_quoted_strings(ltokens);
	return (ltokens);
}

t_token	**merge_word_strings(t_token **cmd_line)
{
	t_token	*tkn;

	tkn = *cmd_line;
	while (tkn && tkn->next)
	{
		if ((tkn->type == WORD || tkn->type == ASSIGN
				|| tkn->type == STR_DQUOTES || tkn->type == STR_SQUOTES)
			&& (tkn->next->type == ASSIGN || tkn->next->type == WORD
				|| tkn->next->type == STR_DQUOTES || tkn->type == STR_SQUOTES))
		{
			tkn->str = ft_strjoin_free_str1(tkn->str, tkn->next->str);
			delete(tkn->next);
		}
		else
			tkn = tkn->next;
	}
	return (cmd_line);
}
