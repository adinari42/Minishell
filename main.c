/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 02:28:56 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

volatile sig_atomic_t	g_stop;

// void	exec_cmd(t_pipe *data, t_dlist **env)
// {
// 	char	**envp;

// 	envp = env_list_to_char_arr(env);
// 	if (!data->parse.path)
// 	{
// 		ms_fd_error(127, data);
// 		exit (127);
// 	}
// 	else
// 	{
// 		if (execve(data->parse.path, data->parse.cmd, envp) == -1)
// 			ms_fd_error(127, data);
// 	}	
// 	free_char_arr(envp);
// 	exit(0);
// }

// void	child(t_pipe *plist, int i)
// {
// 	if (i < plist->cmd_pos)
// 	{
// 		if (dup2(plist->fd[1], 1) == -1)
// 			ms_fd_error(2, plist);
// 	}
// 	if (plist->out_fd != NULL)
// 	{
// 		if (init_outfile(plist))
// 			exit(1);
// 	}
// 	close (plist->fd[0]);
// }

// void	parent(t_pipe *plist)
// {
// 	waitpid(plist->pid, &plist->status, 0);
// 	dup2(plist->fd[0], 0);
// 	close (plist->fd[1]);
// }


/**********/
void call_cmdline(t_token *plist, t_dlist **env, t_pipe *data, int i)
{
	char	*cmd_line;
	t_token	**builtin_list;

	cmd_line = get_cmd(plist, data);
	data->parse.cmd = set_parse_cmd(plist);
	if (cmd_line)
	{
		builtin_list = tokenize(cmd_line);
		if (is_builtin(cmd_line) && !g_stop)
		{
			free(cmd_line);
			data->error_code = handle_builtinstr(*builtin_list, data, i, env);
			error_code(&data->error_code);
		}
		else if (cmd_line && cmd_line[0] && !g_stop)
		{
			free(cmd_line);
			handle_command(data, &plist, i, env);
		}
		else if (cmd_line)
			free(cmd_line);
		free_token_list_and_ptr(builtin_list);
	}
	else
		parent(data);
}

int handle_single_pipe(t_token *plist, t_pipe *data, t_dlist **env, int i)
{
	g_stop = 0;
	pipe(data->fd);
	check_value(plist, *env, data);
	call_cmdline(plist, env, data, i);
	free(data->parse.cmd);
	unlink("tmp");
	return (0);
}

void	main_loop(t_dlist **env, int stdin_rstr, int stdout_rstr, t_pipe *data)
{
	char			*inpt;
	t_token			**list;
	t_token			**plist;

	dup2(stdin_rstr, 0);
	dup2(stdout_rstr, 1);
	reset_term_signals();
	inpt = get_input_line(env, data, stdin_rstr);
	list = read_tokens(inpt);
	free(inpt);
	if (parse(list, data))
		free_token_list_and_ptr(list);
	else
	{
		plist = list_to_pipes(list);
		plist = tabs_to_spaces(plist);
		if (plist)
		{
			signals_blocking_command();
			handle_input(plist, data, env);
		}
		free_pipes(plist);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist			**l_envp;
	int				stdin_restore;
	int				stdout_restore;
	t_pipe			data;

	if (argc != 1)
		return (1);
	l_envp = init_minishell(envp);
	(void) argv;
	stdin_restore = dup(0);
	stdout_restore = dup(1);
	data.error_code = 0;
	while (1)
		main_loop(l_envp, stdin_restore, stdout_restore, &data);
	return (argc);
}
