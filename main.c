/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/15 20:28:25 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_path(t_token *list, char *cmdline, t_parse *parse, t_dlist **env)
{
	t_token	*tklist;
	char	*var_path;
	char	**split_path;

	tklist = list;
	parse->cmd = ft_split(cmdline, ' ');
	var_path = get_value_from_key(*env, "PATH");
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}

void	exec_cmd(t_pipe *data, t_dlist **env)
{
	char	**envp;

	envp = env_list_to_char_arr(env);
	if (!data->parse.path)
	{
		write(2, data->parse.cmd[0], ft_strlen(data->parse.cmd[0]));
		ms_fd_error(127, data);
		exit (127);
	}
	else
		execve(data->parse.path, data->parse.cmd, envp);
	// if (execve(data->parse.path, data->parse.cmd, envp) == -1)
	// 	ms_fd_error(3, data);
	free_char_arr(envp);
	exit(0);
}

int	init_here_doc(t_token *list, t_pipe *pipe)
{
	char	*str;

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
	str = get_next_line(0);
	while (1)
	{
		if (str && ft_strncmp(list->str, str, ft_strlen(str) - 1) == 0)
			break ;
		ft_putstr_fd(str, pipe->file.infile);
		free(str);
		str = get_next_line(0);
	}
	free(str);
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

int	init_outfile(t_pipe *pipe)
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
		ms_fd_error(1, pipe);
		return (1);
	}
	if (dup2(pipe->file.outfile, 1) == -1)
	{
		ms_fd_error(2, pipe);
		return (1);
	}
	close (pipe->file.outfile);
	return (0);
}

void	child(t_pipe *pipe, int i)
{
	if (i != pipe->cmd_pos)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			ms_fd_err(2);
	}
	if (pipe->out_fd != NULL)
	{
		if (init_outfile(pipe))
			ms_fd_error(1, pipe);
	}
	close (pipe->fd[0]);
}

void	parent(t_pipe *pipe)
{
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}


int	init_infile(t_token *list, t_pipe *data, int redir_type)
{
		data->out_fd = NULL;
		if (redir_type == APPEND_IN)
		{	
			if(init_here_doc(list, data))
				return(1);
		}
		else if (redir_type == REDIR_IN)
		{
			data->file.infile = open(list->str, O_RDONLY);
			if (data->file.infile == -1)
			{
				write(2, list->str, ft_strlen(list->str));
				close(data->file.infile);
				ms_fd_error(1, data);
				return (1);
			}
			dup2(data->file.infile, 0);
			close(data->file.infile);
		}
		else if (redir_type == APPEND_OUT)
		{
			data->append = 1;
			data->out_fd = list->str;
		}
		else if (redir_type == REDIR_OUT)
		{
			data->append = 0;
			data->out_fd = list->str;
		}
	return (0);
}

t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			if (init_infile(tmp, data, redir_type) == 1)
				return (NULL);
			return (tmp);
		}
		else if (tmp->type == SPACE_TKN)
			tmp = tmp->next;
		else
		{	
			ms_fd_error(5, data);
			break ;
		}
	}
	return (NULL);
}

char	*get_cmd(t_token *list, t_pipe *data)
{
	t_token	*tmp;
	char	*cmd_line;
	int		redir_type;

	tmp = list;
	cmd_line = ft_strdup("");
	data->out_fd = NULL;
	while (tmp)
	{
		if (tmp->type == APPEND_IN || tmp->type == APPEND_OUT || tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			redir_type = tmp->type;
			tmp = tmp->next;
			tmp = skip_redir(tmp, data, redir_type);//break ;
			if (tmp == NULL)
				return (NULL);
			tmp = tmp->next;
		}
		else
		{
			cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
			if (tmp->type != ASSIGN && (!tmp->next || tmp->next->type != ASSIGN))
				cmd_line = ft_strjoin_free_str1(cmd_line, " ");
			tmp = tmp->next;
		}
	}
	return (cmd_line);
}

void	free_and_close(t_pipe *pipe)
{
	close(pipe->fd[0]);
	close(pipe->fd[1]);
	unlink("tmp");
}

int	handle_input(t_token **pipes, t_pipe *data, t_dlist **env)
{
	int		i;
	int		status;
	char	*cmd_line;
	t_token	*builtin_list;

	data->cmd_pos = count_pipes(pipes);
	i = 0;
	while (pipes[i])
	{
		data->error_code = 0;
		pipe(data->fd);
		pipes[i] = merge_quoted_strings(pipes[i], data);
		if (pipes[i] == NULL)
			return (1);
		check_value(pipes[i], *env);
		cmd_line = get_cmd(pipes[i], data);
		if (cmd_line)
		{
			builtin_list = read_tokens(cmd_line);
			builtin_list = merge_quoted_strings(builtin_list, data);
			builtin_list = remove_empty(builtin_list);
			if (is_builtin(cmd_line) == 1)
				handle_builtinstr(builtin_list, data, i, env);
			else if (is_builtin(cmd_line))
			{
				if (data->out_fd != NULL)
				{
					if (init_outfile(data))
						ms_fd_error(1, data);
				}
				handle_builtin(builtin_list, env);
			}
			else if (cmd_line && cmd_line[0])
				handle_command(pipes[i], data, cmd_line, i, env);
			free_token_list(builtin_list);
			free(cmd_line);
		}
		else
			parent(data);
		i++;
	}
	while (i--) 
      waitpid(-1, &status, 0);
	// printf("Child process exited with code: %d\n", WEXITSTATUS(status));
	return (status);
}

int	main_loop(t_dlist **env, int stdin_restore, int stdout_restore)
{
	int		err;
	char	*inpt;
	t_token	*list;
	t_pipe	data;
	t_token	**pipes;	

	err = 1;
	dup2(stdin_restore, 0);
	dup2(stdout_restore, 1);
	inpt = readline("Minishell$ ");
	if (!inpt)
		free_and_exit(SIGINT, env);		// this does the exit on Ctrl-D
	add_history(inpt);
	list = read_tokens(inpt);
	list = merge_quoted_strings(list, &data);
	pipes = list_to_pipes(list);
	if (pipes && inpt && inpt[0])
		err = handle_input(pipes, &data, env);
	free(inpt);
	free_pipes(pipes);
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist	**l_envp;
	int		stdin_restore;
	int		stdout_restore;

	if (argc != 1)
		return (1);
	l_envp = init_minishell(envp);
	(void) argv; //to silence unused argv error and not use dislay env 
	stdin_restore = dup(0);		// save original stdin/stdout
	stdout_restore = dup(1);
	while (1)
		main_loop(l_envp, stdin_restore, stdout_restore);
	return (argc);
}
