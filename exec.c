/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:50:44 by slakner           #+#    #+#             */
/*   Updated: 2022/11/17 21:45:21 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	die(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(1);
}

int	exec(char *program, char **args, char *const *envp)
{
	pid_t	pid;
	int		link[2];

	(void) program;
	(void) envp;
	char **args2; 

	args2 = ft_split("/bin/ps faux", ' ');

	args = args2;
	args[0] = "/bin/ps";
	args[1] = "faux";

	if (pipe(link) == -1)
		die("pipe");

	pid = fork();
	if (pid == -1)
		die("fork");
	if (!pid)
	{
		printf("PID: %d\n", pid);
		close (link[0]);
		dup2(link[1], 1);
		execve("/bin/sh", NULL, envp);
		execve(args2[0], args2, NULL);//(char *const *) *envp);
		die("execve");
	}
	else
	{
	// // 	printf("main thread, child PID %d\n", pid);
		close(link[1]);
		//dup2(link[0], 0);
	  	waitpid(pid, NULL, 0);
	}
	return (0);
}
