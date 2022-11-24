/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:23 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 19:43:34 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **string, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;

	i = 0;
	while (string[i] != 0)
	{
		path_temp = ft_strjoin(string[i], "/");
		if (!path_temp)
			printf("[Debug] noops path_temp is NULL\n");
		path = ft_strjoin(path_temp, cmd);
		if (!path)
			printf("[Debug] noops path_temp is NULL\n");
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

// void	init_path(t_token *tklist, t_parse parse)
// {
// 	t_token *tmp;
// 	int		iscmd;

// 	iscmd = 1;
// 	tmp = tklist;
// 	printf("init path\b");
// 	while (tmp && tmp->type != PIPE)
// 	{
// 		if (tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES || tmp->type == WORD)
// 			parse.path = tmp->path;
// 		else if (tmp->type == SPACE)
// 			tmp = tmp->next;
// 		else
// 		{
// 			perror("no such file of directory\n");
// 			exit(1);
// 		}
// 	}
// 			// parse.path = ret_path(parse.split_envp, tmp->str);
// 	perror("parse error\n");
// 	exit(1);
// }

void	fd_err(int i)
{
	if (i == 1)
		perror("Unable to open infile\n");
	else if (i == 2)
		perror("Dup2 error\n");
	else if (i == 3)
		perror("Command error\n");
	else if (i == 4)
		perror("Fork error\n");
	else
		perror("Error\n");
	exit(1);
}

// void	exec_cmd(t_pipe *pipe, char *envp[])
// {
// 	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
// 		fd_err(3);
// }

// void	parent(t_pipe *pipe)
// {
// 	dup2(pipe->fd[0], 0);
// 	close (pipe->fd[1]);
// }

// void	child(char *argv[], int argc, int i, t_pipe *pipe)
// {
// 	if (i < argc - 2)
// 	{	
// 		if (dup2(pipe->fd[1], 1) == -1)
// 			fd_err(2);
// 	}
// 	if (i == argc - 2)
// 		init_outfile(argv, argc, pipe);
// 	close (pipe->fd[0]);
// }

// void	free_and_close(t_pipe *pipe)
// {
// 	free_2d(&pipe->parse.split_envp);
// 	close(pipe->fd[0]);
// 	close(pipe->fd[1]);
// 	unlink("tmp");
// }

int	init_here_doc(t_token *tklist, t_pipe *pipe)
{
	char	*str;
	t_token *tmp;

	tmp = tklist;
	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe->file.infile == -1)
		fd_err(1);
	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
		fd_err(1);
	str = get_next_line(0);
	tmp = tmp->next;
	while (tmp->type == SPACE)
		tmp = tmp->next;
	while (1)
	{
		if (ft_strncmp(tmp->str, str, ft_strlen(str) - 1) == 0)
			break ;
		ft_putstr_fd(str, pipe->file.infile);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	pipe->append = 1;
	if (dup2(pipe->file.tmp, 0) == -1)
		fd_err(2);
	close(pipe->file.infile);
	close(pipe->file.tmp);
	return (3);
}
int	init_infile(t_token *tklist, t_pipe *pipe)
{
	t_token *tmp;

	tmp = tklist;
	// argc_err(argc, 5, pipe);
	pipe->append = 0;
	if (tklist->type == APPEND_IN)
	{
		// argc_err(argc, 6, pipe);
		return (init_here_doc(tklist, pipe));
	}
	else
	{
		tmp = tmp->next;
		while (tmp->type == SPACE)
			tmp = tmp->next;
		printf("found infile : %s\n", tmp->str);
		pipe->file.infile = open(tmp->str, O_RDONLY);
		if (pipe->file.infile == -1)
			fd_err(1);
		dup2(pipe->file.infile, 0);
		close(pipe->file.infile);
		return (2);
	}
}
void search_infile(t_token *tklist, t_pipe	pip)
{
	t_token *tmp;

	tmp = tklist;
	while (tmp && tmp->str != PIPE)
	{
		if (tmp->type == REDIR_IN || tmp->type == APPEND_IN)
		{
			init_infile(tmp, &pip);//whatever is on next node of < is infile, if it's in the beginning, execution starts after it, if it's in the end it starts from beginning until <
			break ;
		}
		tmp = tmp->next;
	}
}
// void	execute_line(t_token *list, t_parse parse, char **envp)
// {
// 	t_token *tklist;
// 	t_pipe	pip;
// 	// int		begin;

// 	// begin = 1;
// 	printf("%s\n", parse.path);
// 	tklist = list;
// 	while (tklist)
// 	{
// 		// if (tklist->type == PIPE)
// 			// begin = 1;
// 		pipe(pip.fd);
// 		// if (begin)
// 		search_infile(tklist, pip);
// 		execve("/bin/cat", NULL, envp);
// 		// begin = 0;
// 			// while (tklist)
// 		init_path(tklist, parse);
// 		// printf("cmd path = %s\n", parse.path);
// 		/*pip.pid = fork();
// 		if (pip.pid == -1)
// 			fd_err(4);
// 		if (pip.pid == 0)
// 		{
// 			child(argv, argc, i, &pip);
// 			exec_cmd(&pip, envp);*/
// 	// 	}
// 	// 	else
// 	// 		parent(&pip);
// 	// 	i++;
// 	// 	free_parse(&pip);
// 	// }
// 	// free_and_close(&pip);
// 		sleep(1);
// 		printf("debug 2\n");
// 		while (tklist && tklist->type != PIPE)
// 			tklist = tklist->next;sleep(1);
// 		printf("debug 1\n");
// 	}
// }
