/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 23:19:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 01:06:25 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	open_tmp(t_pipe *pipe)
{
	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe->file.infile == -1)
	{
		ms_fd_error(1, pipe);
		return (1);
	}
	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
	{
		ms_fd_error(1, pipe);
		return (1);
	}
	return (0);
}

void	read_to_tmp(t_token *list, t_pipe *pipe, char	*str)
{
	g_stop = 0;
	while (!g_stop && str)
	{
		write (1, "> ", 2);
		str = get_next_line(0);
		if (str && (!ft_strncmp(list->str, str, ft_strlen(list->str))
				&& !ft_strncmp(str + ft_strlen(list->str), "\n", 1)))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, pipe->file.infile);
		if (str)
			free(str);
	}
}

int	append_in(t_token *list, t_pipe *data)
{
	list->type = INFILE;
	if (init_here_doc(list, data))
		return (1);
	return (0);
}

int	redir_in(t_token *list, t_pipe *data)
{
	list->type = INFILE;
	data->file.infile = open(list->str, O_RDONLY);
	if (data->file.infile == -1)
	{
		data->out_fd = list->str;
		close(data->file.infile);
		ms_fd_error(1, data);
		return (1);
	}
	dup2(data->file.infile, 0);
	close(data->file.infile);
	return (0);
}
