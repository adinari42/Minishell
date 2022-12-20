/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/20 22:05:19 by slakner          ###   ########.fr       */
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

void	init_path(char *cmdline, t_parse *parse, t_dlist **env, t_pipe *data)
{
	char	*var_path;
	char	**split_path;

	parse->cmd = ft_split(cmdline, ' ');
	var_path = get_value_from_key(*env, "PATH", data);
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}


int	handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env) //int stdout_restore, int i)
{
	// (void) i;
	data->pid = fork();
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		handle_builtin(list, env, data);
		exit (0);
	}
	else
		parent(data);
	return (0);
}

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
	return (ret);
}

int	handle_command(t_pipe *data, char *cmd_line, int i, t_dlist **env) //int stdout_restore
{
	int		err;

	err = 0;
	data->pid = fork();
	init_path(cmd_line, &(data->parse), env, data);
	free(cmd_line);
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		exec_cmd(data, env);
	}
	else
		parent(data);
	free_parse(&(data->parse));
	return (err);
}
