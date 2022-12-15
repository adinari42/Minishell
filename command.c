/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/15 18:24:57 by slakner          ###   ########.fr       */
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

int	handle_builtinstr(t_token *list, t_pipe *pipe, int i, t_dlist **env) //int stdout_restore, int i)
{
	
	/*version 1*/
	// (void) i;
	// if (data->out_fd != NULL)
	// 	init_outfile(data);
	// handle_builtin(list, env);
	// parent(data);
	// return (0);

	/*version 2*/
	pipe->pid = fork();
	if (pipe->pid == -1)
		ms_fd_error(4, pipe);
	if (pipe->pid == 0)
	{
		child(pipe, i + 1);
		handle_builtin(list, env);
		exit(0);
	}
	else
		parent(pipe);

	/*another_version*/
	// child(data, i + 1);
	// handle_builtin(list, env);
	// parent(data);

	/*yet again*/
	// (void) env;
	// if (i != pipe->cmd_pos - 1)
	// {	
	// 	if (dup2(pipe->fd[1], 1) == -1)
	// 		ms_fd_err(2);
	// }
	// if (pipe->out_fd != NULL)
	// {
	// 	if (init_outfile(pipe))
	// 		ms_fd_error(1, pipe);
	// }
	// handle_builtin(list, env);
	// parent(pipe);
	return (0);
}

int	handle_builtin(t_token *list)
{
	char	*str;
	int		ret;

	str = (tlist_start(list))->str;
	ret = 0;
	// if (!ft_strncmp(str, g_builtins[ECHO42], 5))
	// 	ret = exec_echo(list);
	if (!ft_strncmp(str, g_builtins[CD], 3))
		ret = exec_cd(list);
	else if (!ft_strncmp(str, g_builtins[PWD], 4))
		ret = exec_pwd(list, *env);
	else if (!ft_strncmp(str, g_builtins[EXPORT], 7))
		ret = exec_export(list, *env);
	else if (!ft_strncmp(str, g_builtins[UNSET], 6))
		ret = exec_unset(list, *env);
	else if (!ft_strncmp(str, g_builtins[ENV], 4))
		ret = exec_env(list, *env);
	else if (!ft_strncmp(str, g_builtins[EXIT], 5))
		ret = exec_exit(list, env);
	return (ret);
}

int	handle_command(t_token *list, t_pipe *data, char *cmd_line, int i) //int stdout_restore
{
	int		err;

	err = 0;
	data->pid = fork();
	init_path(list, cmd_line, &(data->parse));
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		exec_cmd(data);
	}
	else
	{
		parent(data);
		// waitpid(data->pid, &err, 0);
		// write(1, "here\n", 5);
	}
	free_parse(&(data->parse));
	return (err);
}
//must not fork if they are commands after: cd, export, unset, exit
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data)
{
	char	*str;
	int		ret;

	while (list->type == SPACE_TKN)
		list = list->next;
	str = list->str;
	ret = 0;
	if (!ft_strncmp(str, g_builtins[ECHO42], 5))
		ret = exec_echo(list, *env);
	else if (!ft_strncmp(str, g_builtins[CD], 3))
		ret = exec_cd(list, *env);
	else if (!ft_strncmp(str, g_builtins[PWD], 4))
		ret = exec_pwd(list, *env);
	else if (!ft_strncmp(str, g_builtins[EXPORT], 7))
		ret = exec_export(list, *env);
	else if (!ft_strncmp(str, g_builtins[UNSET], 6))
		ret = exec_unset(list, *env);
	else if (!ft_strncmp(str, g_builtins[ENV], 4))
		ret = exec_env(list, *env);
	else if (!ft_strncmp(str, g_builtins[EXIT], 5))
		exec_exit(list, env, data);
	data->error_code = ret;
	return (ret);
}

t_token	**merge_word_strings(t_token **cmd_line)
{
// 	t_token	*new_line;
	t_token	*tkn;

	tkn = *cmd_line;
	while (tkn && tkn->next)
	{
		if ((tkn->type == WORD || tkn->type == ASSIGN) &&
			(tkn->next->type == ASSIGN || tkn->next->type == WORD))
			{
				tkn->str = ft_strjoin_free_str1(tkn->str, tkn->next->str);
				delete(tkn->next);
			}
		else
			tkn = tkn->next;
	}
	return(cmd_line);
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
