/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 14:15:23 by adinari           #+#    #+#             */
/*   Updated: 2022/11/27 17:31:20 by adinari          ###   ########.fr       */
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
	else if (i == 5)
		perror("parse error\n");
	else
		perror("Error\n");
	exit(1);
}
