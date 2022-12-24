/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/24 18:05:17 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

extern volatile int	g_stop;

void	init_path(t_token **cmdline, t_parse *parse, t_dlist **env, t_pipe *data)
{
	char	*var_path;
	char	**split_path;
	int		i;

	i = 0;
	parse->cmd = set_parse_cmd(*cmdline);
	var_path = get_value_from_key(*env, "PATH", data);
	split_path = ft_split(var_path, ':');
	parse->path = get_path(split_path, parse->cmd[0]);
	free_split(split_path);
}

void	exec_cmd(t_pipe *data, t_dlist **env)
{
	// char	**envp;

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

// int	init_here_doc(t_token *list, t_pipe *pipe)
// {
// 	char	*str;

// 	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (pipe->file.infile == -1)
// 	{
// 		ms_fd_error(1, pipe);
// 		return (1);
// 	}
// 	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
// 	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
// 	{
// 		ms_fd_error(1, pipe);
// 		return (1);
// 	}
// 	str = get_next_line(0);
// 	while (1)
// 	{
// 		if (str && ft_strncmp(list->str, str, ft_strlen(str) - 1) == 0)
// 			break ;
// 		ft_putstr_fd(str, pipe->file.infile);
// 		free(str);
// 		str = get_next_line(0);
// 	}
// 	free(str);
// 	pipe->append = 1;
// 	if (dup2(pipe->file.tmp, 0) == -1)
// 	{
// 		ms_fd_error(2, pipe);
// 		return (1);
// 	}
// 	close(pipe->file.infile);
// 	close(pipe->file.tmp);
// 	return (0);
// }

int	init_here_doc(t_token *list, t_pipe *pipe)
{
	char	*str;

	(void) list;
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
	str = ft_strdup("");
	reset_term_signals();
	heredoc_signals(STDIN_FILENO);
	g_stop = 0;
	while (!g_stop && str)
	{
		str = readline("> ");
		if (str && (!ft_strncmp(list->str, str, ft_strlen(str) + 1)))
		{
			free(str);
			break ;
		}
		ft_putstr_fd(str, pipe->file.infile);
		ft_putstr_fd("\n", pipe->file.infile);
		if (str)
			free(str);
	}
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
	//close(pipe->fd[1]);
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
		list->type = INFILE;
		if (init_here_doc(list, data))
			return (1);
	}
	else if (redir_type == REDIR_IN)
	{
		list->type = INFILE;
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

t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			if (init_infile(tmp, data, redir_type))
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

char	*add_quote_char(char *cmd, t_token *tkn)
{
	if (tkn->type == STR_DQUOTES)
		cmd = ft_strjoin_free_str1(cmd, "\"");
	else if (tkn->type == STR_SQUOTES)
		cmd = ft_strjoin_free_str1(cmd, "'");
	return (cmd);
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
			{
				free(cmd_line);
				return (NULL);
			// tmp = tmp->next;
		}
		else
		{
			cmd_line = add_quote_char(cmd_line, tmp);
			cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
			if (tmp->type != ASSIGN && tmp->type != STR_DQUOTES && tmp->type != STR_SQUOTES
				&&  (!tmp->next || tmp->next->type != ASSIGN))
				cmd_line = ft_strjoin_free_str1(cmd_line, " ");
			cmd_line = add_quote_char(cmd_line, tmp);
		}
		tmp = tmp->next;
	}
	return (cmd_line);
}

char**	set_parse_cmd(t_token *head)
{
	int		count;
	t_token	*curr;
	char	**cmd;

	count = 0;
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD || curr->type == STR_DQUOTES 
			|| curr->type == STR_SQUOTES)
			count++;
		curr = curr->next;
	}
	cmd = malloc((count + 1) * sizeof (char *));
	if (cmd == NULL)
	{
		perror("malloc");
		exit(1);
	}
	count = 0;
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == WORD || curr->type == STR_DQUOTES
			|| curr->type == STR_SQUOTES)
			cmd[count++] = curr->str;
		curr = curr->next;
	}
	cmd[count] = NULL;
	return (cmd);
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
	t_token	**builtin_list;

	data->cmd_pos = count_pipes(pipes);
	i = 0;
	while (pipes[i])
	{
		pipe(data->fd);
		if (pipes[i] == NULL)
			return (1);
		check_value(pipes[i], *env, data);
		cmd_line = get_cmd(pipes[i], data);
		data->parse.cmd = set_parse_cmd(pipes[i]);
		if (cmd_line)
		{
			builtin_list = read_tokens(cmd_line);
			builtin_list = merge_quoted_strings(builtin_list);
			if (is_builtin(cmd_line) == 1)
			{
				free(cmd_line);
				handle_builtinstr(*builtin_list, data, i, env);
			}
			else if (is_builtin(cmd_line))
			{
				free(cmd_line);
				if (data->out_fd != NULL)
				{
					if (init_outfile(data))
						ms_fd_error(1, data);
				}
				handle_builtin(*builtin_list, env, data);
			}
			else if (cmd_line && cmd_line[0])
				handle_command(data, &pipes[i], i, env);
			else if (cmd_line)
				free(cmd_line);
			free_token_list(*builtin_list);
			free(builtin_list);
		}
		else
			parent(data);
		unlink("tmp");			// do we need this line?
		i++;
	}
	status = 0;
	waitpid(-1, &status, 0);
	data->error_code = WEXITSTATUS(status);
	return (status);
}

int	main_loop(t_dlist **env, int stdin_restore, int stdout_restore)
{
	int		err;
	char	*inpt;
	t_token	**list;
	t_pipe	data;
	t_token	**pipes;	

	err = 0;
	dup2(stdin_restore, 0);
	dup2(stdout_restore, 1);
	reset_term_signals();
	inpt = readline("Minishell$ ");
	if (!inpt)
		free_and_exit(SIGINT, env);		// this does the exit on Ctrl-D
	add_history(inpt);
	if (is_empty_inpt(inpt))
		return (0);
	list = read_tokens(inpt);
	free(inpt);
	//if (data.error_code || parse(list, &data))
	if (parse(list, &data))
	{
		free_token_list(*list);
		free(list);
	}
	else
	{
		pipes = list_to_pipes(list);
		if (pipes && !err)
		{
			signals_blocking_command();
			err = handle_input(pipes, &data, env);
		}
		free_pipes(pipes);
	}
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
	{
		main_loop(l_envp, stdin_restore, stdout_restore);
		//reset_term_signals();
	}
	return (argc);
}
