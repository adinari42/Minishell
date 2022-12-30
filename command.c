/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 21:05:23 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// I'm assuming that pipes have already been handled at this point
// The argument here would be one 'command' or builtin

// int	handle_commandstr(t_token **list)
// {
// 	char	*str;

// 	list = merge_quoted_strings(list);
// 	if (list && *list)
// 	{
// 		str = (tlist_start(list))->str;
// 		if (is_builtin(str))
// 			return (handle_builtin(list));
// 		else
// 			return (handle_command(list));
// 	}
// 	return (1);
// }

int	handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env, int builtin_id) //int stdout_restore, int i)
{
	int	ret;

	ret = 0;
	if ((builtin_id != 1 && builtin_id != 3 && builtin_id != 6) && data->cmd_pos == 1)
		return(handle_builtin(list, env, data));
	data->pid = fork();
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		if (builtin_id == 1 || builtin_id == 3 || builtin_id == 6 || builtin_id == 7 ) 
			ret = handle_builtin(list, env, data);
		exit (ret);
	}
	else
		parent(data);
	return (ret);
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

//must not fork if they are commands after: cd, export, unset, exit
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data)
{
	char	*str;
	int		ret;
	t_token	**ptr;

	while (list->type == SPACE_TKN)
		list = list->next;
	str = list->str;
	if (!ft_strncmp(str, "export", 7))
	{
		data->error_code = exec_export(list, *env);
		return (data->error_code);
	}
	ptr = &list;
	ptr = merge_word_strings(ptr);
	str = list->str;
	ret = 0;
	if (!ft_strncmp(str, "echo", 5))
		ret = exec_echo(list, *env);
	else if (!ft_strncmp(str, "cd", 3))
		ret = exec_cd(list, *env, data);
	else if (!ft_strncmp(str, "pwd", 4))
		ret = exec_pwd(list, *env);
	else if (!ft_strncmp(str, "unset", 6))
		ret = exec_unset(list, *env);
	else if (!ft_strncmp(str, "env", 4))
		ret = exec_env(list, *env);
	else if (!ft_strncmp(str, "exit", 5))
		exec_exit(list, env, data);
	data->error_code = ret;
	return (ret);
}

int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env) //int stdout_restore
{
	int		err;

	err = 0;
	cmd_line = merge_word_strings(cmd_line);
	data->pid = fork();
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		init_path(cmd_line, &(data->parse), env, data);
		child(data, i + 1);
		exec_cmd(data, env);
		free_parse(&(data->parse));
	}
	else
	{
		parent(data);
	}
	return (err);
}
