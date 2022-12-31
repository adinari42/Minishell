/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:22:41 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 03:05:34 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_token **cmd_l, t_parse *parse, t_dlist **env, t_pipe *data)
{
	char	*var_path;
	char	**split_path;

	parse->cmd = set_parse_cmd(*cmd_l);
	var_path = expand_var_in_str(*env, "PATH", data);
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}

char	**set_parse_cmd(t_token	*head)
{
	int		count;
	t_token	*curr;
	char	**cmd;

	count = 0;
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD || curr->type == STR_DQUOTES
			|| curr->type == STR_SQUOTES)
			count++;
		curr = curr->next;
	}
	cmd = malloc((count + 1) * sizeof (char *));
	count = 0;
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD || curr->type == STR_DQUOTES
			|| curr->type == STR_SQUOTES)
			cmd[count++] = curr->str;
		curr = curr->next;
	}
	cmd[count] = NULL;
	return (cmd);
}

t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	if (!tmp)
	{
		ms_fd_error(258, data);
		return (NULL);
	}
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR_DQUOTES
			|| tmp->type == STR_SQUOTES)
		{
			if (init_infile(tmp, data, redir_type))
				return (NULL);
			return (tmp);
		}
		else if (tmp->type == SPACE_TKN)
			tmp = tmp->next;
		else
		{
			ms_fd_error(258, data);
			break ;
		}
	}
	return (NULL);
}

char	*join_param(char	*cmd_line,	t_token	*tmp)
{
	cmd_line = add_quote_char(cmd_line, tmp);
	cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
	cmd_line = add_quote_char(cmd_line, tmp);
	return (cmd_line);
}

char	*get_cmd(t_token *list, t_pipe *data)
{
	t_token	*tmp;
	char	*cmd_line;
	int		redir_type;

	tmp = list;
	cmd_line = ft_strdup("");
	data->out_fd = NULL;
	while (tmp)
	{
		if (tmp->type == APPEND_IN || tmp->type == APPEND_OUT
			|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			redir_type = tmp->type;
			tmp = tmp->next;
			tmp = skip_redir(tmp, data, redir_type);
			if (tmp == NULL)
			{
				free(cmd_line);
				return (NULL);
			}
		}
		else
			cmd_line = join_param(cmd_line, tmp);
		tmp = tmp->next;
	}
	return (cmd_line);
}
