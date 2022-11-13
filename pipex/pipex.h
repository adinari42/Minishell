/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:20:09 by adinari           #+#    #+#             */
/*   Updated: 2022/11/12 22:51:43 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

typedef struct file
{
	int	infile;
	int	outfile;
	int	tmp;
}				t_file;

typedef struct parse
{
	char	**cmd;
	char	**split_envp;
	char	*path;
}				t_parse;

typedef struct pipe
{
	int		fd[2];
	pid_t	pid;
	t_file	file;
	t_parse	parse;
	int		error_code;
	int		append;
}				t_pipe;

int		init_here_doc(char *argv[], t_pipe *pipe);
void	child(char *argv[], int argc, int i, t_pipe *pipe);
void	parent(t_pipe *pipe);
void	init_outfile(char *argv[], int argc, t_pipe *pipe);
int		init_infile(char *argv[], int argc, t_pipe *pipe);
void	free_2d(char ***to_free);
void	argc_err(int argc, int n, t_pipe *pipe);
void	fd_err(int i);
void	exec_cmd(t_pipe *pipe, char *envp[]);
void	free_parse(t_pipe *pipe);

#endif