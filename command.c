/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/26 12:09:44 by adinari          ###   ########.fr       */
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
	if ((builtin_id != 1 && builtin_id != 3 && builtin_id != 6) && data->cmd_pos < 2)
		handle_builtin(list, env, data);
	data->pid = fork();
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		if (builtin_id == 1 || builtin_id == 3 || builtin_id == 6 || builtin_id == 7 ) 
			handle_builtin(list, env, data);
		exit (0);
	}
	else
		parent(data);
	return (0);
}
//must not fork if they are commands after: cd, export, unset, exit
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data)
{
	char	*str;
	int		ret;

	while (list->type == SPACE_TKN)
		list = list-> next;
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

int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env) //int stdout_restore
{
	int		err;

	err = 0;
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
