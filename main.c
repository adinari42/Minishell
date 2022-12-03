/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/03 14:24:28 by slakner          ###   ########.fr       */
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
	free(cmdline);
	var_path = get_value_from_key(*g_env, "PATH");
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}

void	exec_cmd(t_pipe *pipe)
{
	char	**envp;

	envp = env_list_to_char_arr(g_env);
	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
		fd_err(3);
	free_split(envp);
}

int	init_here_doc(t_token *list, t_pipe *pipe)
{
	char	*str;

	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe->file.infile == -1)
		fd_err(1);
	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
		fd_err(2);
	str = get_next_line(0);
	while (1)
	{
		if (ft_strncmp(list->str, str, ft_strlen(str) - 1) == 0)
			break ;
		ft_putstr_fd(str, pipe->file.infile);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	pipe->append = 1;
	if (dup2(pipe->file.tmp, 0) == -1)
		fd_err(2);
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
		fd_err(1);
	if (dup2(pipe->file.outfile, 1) == -1)
		fd_err(2);
	close (pipe->file.outfile);
}
void	child(t_pipe *pipe)
{
	if (i != pipe->cmd_pos)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			fd_err(2);
	}
	if (pipe->out_fd != NULL)
	{
		init_outfile(pipe);
	}
	// close (pipe->fd[0]);
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
				fd_err(1);
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
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			init_infile(tmp, data, redir_type);
			tmp = tmp->next;
			return (tmp);
		}
		else if (tmp->type == SPACE)
			tmp = tmp->next;
		else
			fd_err(5);
	}
	fd_err(5);
	return (tmp);
}

char	*get_cmd(t_token *list, t_pipe *data)
{
	t_token *tmp;
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
		}
		else	
		{
			char *tmp1;
			tmp1 = cmd_line;
			cmd_line = ft_strjoin(cmd_line, tmp->str);
			free(tmp1);
			tmp1 = cmd_line;
			// printf("ptr : %p\n", cmd_line);
			cmd_line = ft_strjoin(cmd_line, " ");
			free(tmp1);
			// printf("ptr : %p\n", cmd_line);
			tmp = tmp->next;
		}
	}
	return (cmd_line);
}

void	free_and_close(t_pipe *pipe)
{
	free_2d(&pipe->parse.split_envp);
	// close(pipe->fd[0]);
	// close(pipe->fd[1]);
	unlink("tmp");
}

void	parent(t_pipe *pipe)
{
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}

int	count_split_elems(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] && arr[i][0])
		i ++;
	return (i);
}

int	handle_input(char **inpt_split, t_pipe *data, char **envp, int stdout_restore)
{
	int		i;
	int		err;
	t_token	**list;
	char	*cmd_line;
	t_token	**builtin_list;

	//(void) stdout_restore;
	data->cmd_pos = count_split_elems(inpt_split);
	i = 0;
	err = 0;
	while (inpt_split[i])
	{
		pipe(data->fd);
		list = read_tokens(inpt_split[i]);
		list = merge_quoted_strings(list);
		check_value(*list, envp);
		cmd_line = get_cmd(*list, data);
		builtin_list = read_tokens(cmd_line);
		builtin_list = merge_quoted_strings(builtin_list);
		builtin_list = remove_empty(builtin_list);
		if (is_builtin(cmd_line))
		{
			handle_builtin(builtin_list);
		}
		else
		{
			handle_command(list, data, stdout_restore, i);
		}
		free(cmd_line);
		free_token_list(list);
		if (builtin_list)
			free_token_list(builtin_list);
		i++;
	}
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	int		stdin_restore;
	int		stdout_restore;
	int		err;
	t_pipe	data;
	char	*inpt;
	char	**inpt_split;

	if (argc != 1)
		return (1);
	init_signals();
	init_env_llist(envp);
	(void) argv; //to silence unused argv error and not use dislay env 
	//data.parse.split_envp = envp_parse(envp);
	stdin_restore = dup(0);		// save original stdin/stdout
	stdout_restore = dup(1);
	while (1)
	{
		dup2(stdin_restore, 0);
		inpt = readline("Minishell$ ");
		add_history(inpt);
		inpt_split = ft_split(inpt, '|');
		free(inpt);
		if (inpt && inpt[0])
			err = handle_input(inpt_split, &data, envp, stdout_restore);
		if (inpt)
			free(inpt);
		free_char_arr(inpt_split);
		unlink("tmp");
	}
	//free_char_arr(data.parse.split_envp);
	return (argc);
}
