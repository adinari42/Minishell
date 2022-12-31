/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 01:50:03 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 01:50:28 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_pipe *data, t_dlist **env)
{
	char	**envp;

	envp = env_list_to_char_arr(env);
	if (!data->parse.path)
	{
		ms_fd_error(127, data);
		exit (127);
	}
	else
	{
		if (execve(data->parse.path, data->parse.cmd, envp) == -1)
			ms_fd_error(127, data);
	}	
	free_char_arr(envp);
	exit(0);
}

void	child(t_pipe *plist, int i)
{
	if (i < plist->cmd_pos)
	{
		if (dup2(plist->fd[1], 1) == -1)
			ms_fd_error(2, plist);
	}
	if (plist->out_fd != NULL)
	{
		if (init_outfile(plist))
			exit(1);
	}
	close (plist->fd[0]);
}

void	parent(t_pipe *plist)
{
	waitpid(plist->pid, &plist->status, 0);
	dup2(plist->fd[0], 0);
	close (plist->fd[1]);
}
