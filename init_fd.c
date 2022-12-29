/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 22:09:19 by adinari           #+#    #+#             */
/*   Updated: 2022/12/29 05:46:42 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"


int		init_here_doc(t_token *list, t_pipe *pipe)
{
	char	*str;

	if (open_tmp(pipe))
		return (1);
	str = ft_strdup("");
	reset_term_signals();
	heredoc_signals(STDIN_FILENO);
	read_to_tmp(list, pipe, str);
	signals_blocking_command();
	pipe->append = 1;
	if (dup2(pipe->file.tmp, 0) == -1)
	{
		ms_fd_error(2, pipe);
		return (1);
	}
	close(pipe->file.infile);
	close(pipe->file.tmp);
	return (0);
}

int		init_infile(t_token *list, t_pipe *data, int redir_type)
{
	data->out_fd = NULL;
	if (redir_type == APPEND_IN)
		return(append_in(list, data));
	else if (redir_type == REDIR_IN)
		return (redir_in(list, data));
	else if (redir_type == APPEND_OUT)
	{
		list->type = OUTFILE;
		data->append = 1;
		data->out_fd = list->str;
	}
	else if (redir_type == REDIR_OUT)
	{
		list->type = OUTFILE;
		data->append = 0;
		data->out_fd = list->str;
	}
	return (0);
}

int		init_outfile(t_pipe *pipe)
{
	if (pipe->append == 0)
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	pipe->append = 0;
	if (pipe->file.outfile == -1)
	{
		// pipe->file.infile = pipe->out_fd;
		ms_fd_error(6, pipe);
		return (1);
	}
	else if (dup2(pipe->file.outfile, 1) == -1)
	{
		ms_fd_error(2, pipe);
		return (1);
	}
	close (pipe->file.outfile);
	return (0);
}