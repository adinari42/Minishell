/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/11 21:34:17 by slakner          ###   ########.fr       */
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

void	exec_cmd(t_pipe *pipe, t_dlist **env)
{
	char	**envp;

	envp = env_list_to_char_arr(env);
	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
		ms_fd_err(3);
}

int	init_here_doc(t_token *list, t_pipe *pipe)
{
	char	*str;

	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe->file.infile == -1)
		ms_fd_err(1);
	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
		ms_fd_err(2);
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
		ms_fd_err(2);
	close(pipe->file.infile);
	close(pipe->file.tmp);
	return (3);
}

void	init_outfile(t_pipe *pipe)
{
	if (pipe->append == 0)
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		pipe->file.outfile = open(pipe->out_fd,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(pipe->out_fd);
	pipe->append = 0;
	if (pipe->file.outfile == -1)
		ms_fd_err(1);
	if (dup2(pipe->file.outfile, 1) == -1)
		ms_fd_err(2);
	close (pipe->file.outfile);
}

void	child(t_pipe *pipe, int i)
{
	close (pipe->fd[0]);
	if (i != pipe->cmd_pos)			// cmd_pos marks the last pipe(?)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			ms_fd_err(2);
	}
	if (pipe->out_fd != NULL)
		init_outfile(pipe);
	close(pipe->fd[1]);
}

void	parent(t_pipe *pipe)
{
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}


void	init_infile(t_token *list, t_pipe *pipe, int redir_type)
{
		if (pipe->out_fd)
			free(pipe->out_fd);
		pipe->out_fd = NULL;
		if (redir_type == APPEND_IN)
			init_here_doc(list, pipe);
		else if (redir_type == REDIR_IN)
		{
			pipe->file.infile = open(list->str, O_RDONLY);
			if (pipe->file.infile == -1)
				ms_fd_err(1);
			dup2(pipe->file.infile, 0);
			close(pipe->file.infile);
		}
		else if (redir_type == APPEND_OUT)
		{
			pipe->append = 1;
			pipe->out_fd = list->str;
		}
		else if (redir_type == REDIR_OUT)
		{
			pipe->append = 0;
			pipe->out_fd = list->str;
		}
}

t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	while (tmp)
	{
		// printf("skip_redir : while tmp, tmp->str = %s\n", tmp->str);
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			init_infile(tmp, data, redir_type);
			tmp = tmp->next;
			return (tmp);
		}
		else if (tmp->type == SPACE_TKN)
			tmp = tmp->next;
		else
			ms_fd_err(5);
	}
	ms_fd_err(5);
	return (tmp);
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
	// (void) pipes;
	// (void) data;
	//(void) env;

	int		i;
	int		err;
	char	*cmd_line;
	t_token	*builtin_list;

	data->cmd_pos = count_split_elems(inpt_split);
	i = 0;
	err = 0;
	while (inpt_split[i])
	{
		pipe(data->fd);
		check_value(pipes[i], *env);
		cmd_line = get_cmd(pipes[i], data);
		builtin_list = read_tokens(cmd_line);
		builtin_list = merge_quoted_strings(builtin_list, data);
		builtin_list = remove_empty(builtin_list);
		if (is_builtin(cmd_line))
			handle_builtinstr(builtin_list, data, i, env);
		else if (cmd_line && cmd_line[0])
			handle_command(pipes[i], data, cmd_line, i, env);
		free(cmd_line);
		//free_token_list(list);		// this was freeing part of "**pipes" and led to double free later
		free_token_list(builtin_list);
		// }
		i++;
	}
	return (err);
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
