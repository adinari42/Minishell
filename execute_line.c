/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:23 by adinari           #+#    #+#             */
/*   Updated: 2022/12/29 18:33:56 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **string, char *cmd)
{
	int		i;
	char	*path;
	char	*path_temp;

	i = 0;
	while (cmd && string[i] != 0)
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
		if (path)
			free(path);
		i++;
	}
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

// void	ms_fd_err(int i)
// {
// 	if (i == 1)
// 		perror("Unable to open infile\n");
// 	else if (i == 2)
// 		perror("Dup2 error\n");
// 	else if (i == 3)
// 		perror("Command error\n");
// 	else if (i == 4)
// 		perror("Fork error\n");
// 	else if (i == 5)
// 		perror("parse error\n");
// 	else if (i == 258)	
// 		dprintf(2, "systax error: unclosed quotes\n");
// 	else
// 		perror("Error\n");
// 	exit(i);
// }

void	ms_fd_error(int i, t_pipe *data)
{
	data->pid = fork();
  if (data->pid < 0) {
    write(2,  ": Failed to create child process\n", 31);
    exit(EXIT_FAILURE);
  } else if (data->pid == 0) {
	write(2, "Minishell: ", 12);
	if (i == 1 || i == 6)
	{
		write(2, data->out_fd, ft_strlen(data->out_fd));
		if (i == 1)
			write(2, ": Could not open file or directory\n", 35);
		else if (i == 6)
			write(2, ": Permission denied\n", 20);
	}
	else if (i == 2)
		write(2, "Dup2 error\n", 13);
	else if (i == 3)
		write(2, "Command error\n", 16);
	else if (i == 4)
		write(2, "Fork error\n", 13);
	else if (i == 5)
		write(2, "parse error\n", 14);
	else if (i == 127)
	{
		write(2, data->parse.cmd[0], ft_strlen(data->parse.cmd[0]));
		write(2, ": Command not found\n", 20);
	}
	else if (i == 258)	
		write(2, "systax error\n", 32);
	else
		write(2, "Error\n", 8);
	data->error_code = i;
	exit(i);
  } 
}
