/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:39:48 by slakner           #+#    #+#             */
/*   Updated: 2022/11/14 23:14:00 by slakner          ###   ########.fr       */
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
		return(SPACE);
	else
		return (WORD);
}

void print_list(t_token *tklist)
{
	if (!tklist)
		return;

	int i = 0;
	while (tklist)
	{
		printf(">%s\n", tklist->str);
		tklist = tklist->next;
		i++;
	}
	return ;
}


t_token	**read_tokens(char *bashcmd)
{
	const char	spec_c[] = "\"'<>| ";
	t_token		*token;
	t_token		**tk_list;
	size_t		word_s;
	size_t		i;
	char		*tokenstr;

	tk_list = malloc(sizeof(t_list *));
	*tk_list = NULL;
	word_s = 0;
	i = 0;
	while (i < ft_strlen(bashcmd))
	{
		if (char_in_charset(bashcmd[i], spec_c) || bashcmd[i] == ' ')
		{
			if (i - word_s > 1) // we need to save the previous word
			{
				tokenstr = ft_substr(bashcmd, word_s, i - word_s); //TODO: free this
				token = token_new(tokenstr);
				append(tk_list, token);
			}
			//now save the char that we just found
			if (i < ft_strlen(bashcmd) - 1
				&& bashcmd[i] == '<' && bashcmd[i + 1] == '<' && i++)
				tokenstr = ft_strdup("<<");
			else if (i < ft_strlen(bashcmd) - 1
				&& bashcmd[i] == '>' && bashcmd[i + 1] == '>' && i++)
				tokenstr = ft_strdup(">>");
			else
				token = token_new(ft_substr(bashcmd, i, 1));
			word_s = i + 1;
			append(tk_list, token);
		}
		i++;
	}
	if (word_s < i)
	{
		tokenstr = ft_substr(bashcmd, word_s, i - word_s);
		append(tk_list, token_new(tokenstr));
		free(tokenstr);
	}
	print_list(*tk_list);
	return (tk_list);
}
