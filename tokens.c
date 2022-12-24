/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:39:48 by slakner           #+#    #+#             */
/*   Updated: 2022/12/23 23:30:55 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	char_in_charset(char c, const char *charset)
{
	char	*ptr;

	ptr = (char *) charset;
	while (*ptr)
	{
		if (c == *ptr)
			return (1);
		ptr ++;
	}
	return (0);
}

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
	else if (!ft_strncmp(c, " ", 1))
		return (SPACE_TKN);
	else if (!ft_strncmp(c, "=", 1))
		return (ASSIGN);
	else
		return (WORD);
}

void	print_list(t_token *list)
{
	t_token	*tklist;

	tklist = list;
	if (!tklist)
		return ;
	while (tklist)
	{
		printf(">%s %d\n", tklist->str, tklist->type);
		tklist = tklist->next;
	}
	return ;
}

t_token	*read_tokens(char *bashcmd)
{
	const char	spec_c[] = "\"'<>| =";
	t_token		*tk_list;
	size_t		word_s;
	size_t		i;
	char		*tokenstr;

	//tk_list = malloc(sizeof(t_list));
	tk_list = NULL;
	word_s = 0;
	i = 0;
	while (i < ft_strlen(bashcmd))
	{
		if (char_in_charset(bashcmd[i], spec_c) || bashcmd[i] == ' ')
		{
			if (i - word_s > 0) // we need to save the previous word
			{
				tokenstr = ft_substr(bashcmd, word_s, i - word_s);
				tappend(&tk_list, token_new(tokenstr));
				free(tokenstr);
			}
			//now save the char that we just found
			if (i < ft_strlen(bashcmd) - 1
				&& bashcmd[i] == '<' && bashcmd[i + 1] == '<' && ++i)
				tokenstr = ft_strdup("<<");
			else if (i < ft_strlen(bashcmd) - 1
				&& bashcmd[i] == '>' && bashcmd[i + 1] == '>' && ++i)
				tokenstr = ft_strdup(">>");
			else
				tokenstr = ft_substr(bashcmd, i, 1);
			word_s = i + 1;
			tappend(&tk_list, token_new(tokenstr));
			free(tokenstr);
		}
		i++;
	}
	if (word_s < i)
	{
		tokenstr = ft_substr(bashcmd, word_s, i - word_s);
		tappend(&tk_list, token_new(tokenstr));
		free(tokenstr);
	}
	return (tk_list);
}
