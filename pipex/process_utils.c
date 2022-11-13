/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 23:18:53 by adinari           #+#    #+#             */
/*   Updated: 2022/10/25 00:16:27 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_infile(char *argv[], int argc, t_pipe *pipe)
{
	argc_err(argc, 5, pipe);
	pipe->append = 0;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		argc_err(argc, 6, pipe);
		return (init_here_doc(argv, pipe));
	}
	else
	{
		pipe->file.infile = open(argv[1], O_RDONLY);
		if (pipe->file.infile == -1)
			fd_err(1);
		dup2(pipe->file.infile, 0);
		close(pipe->file.infile);
		return (2);
	}
}

void	init_outfile(char *argv[], int argc, t_pipe *pipe)
{
	if (pipe->append == 0)
		pipe->file.outfile = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		pipe->file.outfile = open(argv[argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipe->file.outfile == -1)
		fd_err(1);
	if (dup2(pipe->file.outfile, 1) == -1)
		fd_err(2);
}

void	child(char *argv[], int argc, int i, t_pipe *pipe)
{
	if (i < argc - 2)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			fd_err(2);
	}
	if (i == argc - 2)
		init_outfile(argv, argc, pipe);
	close (pipe->fd[0]);
}

void	exec_cmd(t_pipe *pipe, char *envp[])
{
	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
		fd_err(3);
}

void	parent(t_pipe *pipe)
{
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}
