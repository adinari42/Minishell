/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:14:57 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 03:57:46 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env)
{
	int	builtin_id;
	int	ret;

	ret = 0;
	while (list->type == SPACE_TKN)
		list = list->next;
	builtin_id = is_builtin(list->str);
	if (builtin_id != 1 && builtin_id != 3 && builtin_id != 6
		&& data->cmd_pos == 1)
		return (handle_builtin(list, env, data));
	data->pid = fork();
	if (data->pid == -1)
		ms_fd_error(4, data);
	if (data->pid == 0)
	{
		child(data, i + 1);
		if (builtin_id == 1 || builtin_id == 3 || builtin_id == 6
			|| builtin_id == 7)
			ret = handle_builtin(list, env, data);
		exit (ret);
	}
	else
		parent(data);
	return (ret);
}

int	handle_nonexport_builtin(t_token *list, t_dlist **env, t_pipe *data)
{
	t_token	**ptr;
	int		ret;

	ptr = &list;
	ptr = merge_word_strings(ptr);
	ret = 0;
	if (!ft_strncmp(list->str, "echo", 5))
		ret = exec_echo(list, *env);
	else if (!ft_strncmp(list->str, "cd", 3))
		ret = exec_cd(list, *env, data);
	else if (!ft_strncmp(list->str, "pwd", 4))
		ret = exec_pwd(list, *env);
	else if (!ft_strncmp(list->str, "unset", 6))
		ret = exec_unset(list, *env);
	else if (!ft_strncmp(list->str, "env", 4))
		ret = exec_env(list, *env);
	else if (!ft_strncmp(list->str, "exit", 5))
		ret = exec_exit(list, env, data);
	data->error_code = ret;
	return (ret);
}

//must not fork if they are commands after: cd, export, unset, exit
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data)
{
	while (list->type == SPACE_TKN)
		list = list->next;
	if (!ft_strncmp(list->str, "export", 7))
	{
		data->error_code = exec_export(list, *env);
		return (data->error_code);
	}
	return (handle_nonexport_builtin(list, env, data));
}

int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env)
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
		parent(data);
	return (err);
}

void	treat_cmdline(t_token *plist, t_pipe *data, t_dlist **env, int i)
{
	t_token	**builtin_list;

	builtin_list = read_tokens(data->cmd_line);
	builtin_list = merge_quoted_strings(builtin_list);
	if (is_builtin(data->cmd_line) && !g_stop)
	{
		free(data->cmd_line);
		data->error_code = handle_builtinstr(*builtin_list, data, i, env);
		error_code(&data->error_code);
	}
	else if (data->cmd_line && data->cmd_line[0] && !g_stop)
	{
		free(data->cmd_line);
		handle_command(data, &plist, i, env);
	}
	else if (data->cmd_line)
		free(data->cmd_line);
	free_token_list(*builtin_list);
	free(builtin_list);
}
