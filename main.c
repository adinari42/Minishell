/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/13 08:13:02 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// commented because I don't think this is used anywhere anymore
// for debugging?
// void	display_splitenvp(t_parse parse, char **argv)
// {
// 	int	i;

// 	i = 0;
// 	printf("%s envp parse: ", argv[0]);
// 	while (parse.split_envp[i])
// 		printf("%s\n", parse.split_envp[i++]);
// }

void	init_path(t_token *list, char *cmdline, t_parse *parse)
{
	t_token	*tklist;
	char	*var_path;
	char	**split_path;

	tklist = list;
	parse->cmd = ft_split(cmdline, ' ');
	var_path = get_value_from_key(*g_env, "PATH");
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}

void	exec_cmd(t_pipe *data)
{
	char	**envp;

	envp = env_list_to_char_arr(g_env);
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
	// printf("init outfile\n");
	if (pipe->append == 0)
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(pipe->out_fd);
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
	// printf("child\n");
	if (i != pipe->cmd_pos)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			ms_fd_err(2);
	}
	// printf("out_fd = %s\n", pipe->out_fd);
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
		if (data->out_fd)
			free(data->out_fd);
		data->out_fd = NULL;
		if (redir_type == APPEND_IN)
		{	if(init_here_doc(list, data))
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
			// printf("redirout:\n");
			data->append = 0;
			data->out_fd = list->str;
			// printf("data->out_fd = %s\n", data->out_fd);
		}
	return (0);
}

t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	while (tmp)
	{
		// printf("skip_redir : while tmp, tmp->str = %s\n", tmp->str);
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			// printf("inside if\n");
			if (init_infile(tmp, data, redir_type) == 1)
				return (NULL);
			// printf("still inside if,\n");
			// tmp = tmp->next;
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
	// ms_fd_error(5, data);
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
		// printf("get_cmd : while tmp, tmp->str = %s\n", tmp->str);
		if (tmp->type == APPEND_IN || tmp->type == APPEND_OUT || tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			redir_type = tmp->type;
			tmp = tmp->next;
			tmp = skip_redir(tmp, data, redir_type);//break ;
			if (tmp == NULL)
			{
				// printf("tmp = null\n");
				return (NULL);
			}
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

int	handle_input(t_token **pipes, t_pipe *data)
{
	// (void) pipes;
	// (void) data;

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
		check_value(pipes[i]);
		cmd_line = get_cmd(pipes[i], data);
		// printf("cmd_line = %s\n", cmd_line);
		if (cmd_line)
		{	//printf("inside if\n");
			builtin_list = read_tokens(cmd_line);
			builtin_list = merge_quoted_strings(builtin_list, data);
			builtin_list = remove_empty(builtin_list);
			if (is_builtin(cmd_line))
				handle_builtinstr(builtin_list, data, i);
			else if (cmd_line && cmd_line[0])
				handle_command(pipes[i], data, cmd_line, i);
			//free_token_list(list);		// this was freeing part of "**pipes" and led to double free later
			free_token_list(builtin_list);
			free(cmd_line);
		}
		else
		{	
			// printf("parent:\n");
			parent(data);
		}
		i++;
	}
	while (i--) 
      waitpid(-1, &status, 0);
	// printf("Child process exited with code: %d\n", WEXITSTATUS(status));
	return (status);
}

int	main(int argc, char **argv, char **envp)
{
	int		stdin_restore;
	int		stdout_restore;
	int		err;
	t_pipe	data;
	char	*inpt;
	t_token	**pipes;
	t_token *list;

	if (argc != 1)
		return (1);
	init_minishell(envp);
	(void) argv; //to silence unused argv error and not use dislay env 
	stdin_restore = dup(0);		// save original stdin/stdout
	stdout_restore = dup(1);
	while (1)
	{
		dup2(stdin_restore, 0);
		dup2(stdout_restore, 1);
		inpt = readline("Minishell$ ");
		if (!inpt)
			free_and_exit(SIGINT);		// this does the exit on Ctrl-D
		add_history(inpt);
		list = read_tokens(inpt);
		list = merge_quoted_strings(list, &data);
		pipes = list_to_pipes(list);
		if (pipes && inpt && inpt[0])
			err = handle_input(pipes, &data);
		if (inpt)
			free(inpt);
		free_pipes(pipes);
	}
	return (argc);
}
