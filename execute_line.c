/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:23 by adinari           #+#    #+#             */
/*   Updated: 2022/12/19 23:22:18 by slakner          ###   ########.fr       */
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

void	ms_fd_err(int i)
{
	if (i == 1)
		perror("Unable to open infile\n");
	else if (i == 2)
		perror("Dup2 error\n");
	else if (i == 3)
		perror("Command error\n");
	else if (i == 4)
		perror("Fork error\n");
	else if (i == 5)
		perror("parse error\n");
	else if (i == 258)	
		dprintf(2, "systax error: unclosed quotes\n");
	else
		perror("Error\n");
	exit(i);
}

void	ms_fd_error(int i, t_pipe *data)
{
	// int	status;

	data->pid = fork();  
  if (data->pid < 0) {
    // Error occurred while creating child process
    dprintf(2,  "Failed to create child process\n");
    exit(EXIT_FAILURE);
  } else if (data->pid == 0) {
    // Inside the child process
	if (i == 1)
		write(2, ": Could not open file or directory\n", 35);
	else if (i == 2)
		dprintf(2, "Dup2 error\n");
	else if (i == 3)
		dprintf(2, "Command error\n");
	else if (i == 4)
		dprintf(2, "Fork error\n");
	else if (i == 5)
		dprintf(2, ": parse error\n");
	else if (i == 127)
		write(2, " : Command not found\n", 21);
	else if (i == 258)	
		dprintf(2, "systax error: unclosed quotes\n");
	else
		dprintf(2, "Error\n");
	data->error_code = i;
	// if (i == 127 || i == 3)
	// 	exit(i);
	exit(i);
  } 
//   else {
// 	waitpid(data->pid, &status, 0);
// 	data->error_code = WEXITSTATUS(status);
    // Inside the parent process
    // Child process was created successfully
//   }
}
/*
    if (errno == ENOENT) {
      // File doesn't exist
      fprintf(stderr, "Error: File %s doesn't exist\n", argv[1]);
      return 2;
    } else if (errno == EACCES) {
      // File doesn't have the necessary permissions for reading and writing
      fprintf(stderr, "Error: No permission to read/write file %s\n", argv[1]);
*/