/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/21 15:52:19 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// I'm assuming that pipes have already been handled at this point
// The argument here would be one 'command' or builtin

int	handle_commandstr(t_token **list)
{
	char	*str;

	if (list && *list)
	{
		str = (tlist_start(list))->str;
		if (is_builtin(str))
			return (handle_builtin(list));
		else
			return (handle_command(list));
	}
	return (1);
}

int	handle_builtin(t_token **list)
{
	char	*str;
	int		ret;

	str = (tlist_start(list))->str;
	ret = 0;
	if (!ft_strncmp(str, g_builtins[ECHO], 5))
		ret = exec_echo(list);
	else if (!ft_strncmp(str, g_builtins[CD], 3))
		ret = exec_cd(list);
	else if (!ft_strncmp(str, g_builtins[PWD], 4))
		ret = exec_pwd(list);
	else if (!ft_strncmp(str, g_builtins[EXPORT], 7))
		ret = exec_export(list);
	else if (!ft_strncmp(str, g_builtins[UNSET], 6))
		ret = exec_unset(list);
	else if (!ft_strncmp(str, g_builtins[ENV], 4))
		ret = exec_env(list);
	else if (!ft_strncmp(str, g_builtins[EXIT], 5))
		exec_exit(list, env, data);
	data->error_code = ret;
	return (ret);
}

int	handle_command(t_token **list)
{
	int		err;
	//char	*cmd;

	err = 0;
	// (void) list;
	// (void) i;
	// (void) stdout_restore;
	// (void) data;
	data->pid = fork();
	//cmd = get_cmd(*list, data);
	init_path(*list, get_cmd(*list, data), &(data->parse));
	dup2(stdout_restore, 1);
	if (data->pid == -1)
		fd_err(4);
	if (data->pid == 0)
	{
		child(data, i + 1);
		exec_cmd(data);
		exit(1);
	}
	else
	{
		parent(data);
		waitpid(data->pid, &err, 0);
	}
	free_parse(&(data->parse));
	return (err);
}
