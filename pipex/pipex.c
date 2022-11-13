/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:32:59 by adinari           #+#    #+#             */
/*   Updated: 2022/10/25 00:17:00 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "pipex.h"
#include "libft/libft.h"
#include <fcntl.h>

//this version takes care of multiple pipes with direct path or single command.
// structure presentation :
//https://miro.com/app/board/uXjVPO5HwXk=/?share_link_id=144382794819
char	**ft_split(char const *s, char c);

char	*ret_path(char **string, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;

	i = 0;
	while (string[i] != 0)
	{
		path_temp = ft_strjoin(string[i], "/");
		path = ft_strjoin(path_temp, cmd);
		free(path_temp);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

char	**envp_parse(char **envp)
{
	int		j;
	char	**envp_parse;

	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], "PATH=", 5))
			break ;
	}
	envp_parse = ft_split(*(envp + j) + 5, ':');
	return (envp_parse);
}

void	init_path(char **argv, int i, t_pipe *pipe)
{
	pipe->parse.cmd = ft_split(argv[i], ' ');
	pipe->parse.path = ret_path(pipe->parse.split_envp,
			pipe->parse.cmd[0]);
}

void	free_and_close(t_pipe *pipe)
{
	free_2d(&pipe->parse.split_envp);
	close(pipe->fd[0]);
	close(pipe->fd[1]);
	unlink("tmp");
}

/*
init_infile : -opens/creates infile and redirects it as stdin
		-works as input for first cmd
init_path : parses environment and returns proper path of the cmd
child : redirects it's stdout to fd[1], then execve to run the proper cmd
parent : redirects fd[0] of cmd to stdin so it becomes input of next cmd
*/
int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	t_pipe	pip;

	pip.parse.split_envp = envp_parse(envp);
	i = 0;
	while (i <= argc - 2)
	{
		pipe(pip.fd);
		if (i == 0)
			i = init_infile(argv, argc, &pip);
		init_path(argv, i, &pip);
		pip.pid = fork();
		if (pip.pid == -1)
			fd_err(4);
		if (pip.pid == 0)
		{
			child(argv, argc, i, &pip);
			exec_cmd(&pip, envp);
		}
		else
			parent(&pip);
		i++;
		free_parse(&pip);
	}
	free_and_close(&pip);
}
