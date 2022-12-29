/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/29 19:06:02 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_stop;

void	init_path(t_token **cmdline, t_parse *parse, t_dlist **env, t_pipe *data)
{
	char	*var_path;
	char	**split_path;

	parse->cmd = set_parse_cmd(*cmdline);
	var_path = get_value_from_key(*env, "PATH", data);
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
		ms_fd_error(127, data);
		exit (127);
	}
	else
	{
		if (execve(data->parse.path, data->parse.cmd, envp) == -1)
			ms_fd_error(127, data);
	}	
	free_char_arr(envp);
	exit(0);
}


void	child(t_pipe *pipe, int i)
{
	if (i < pipe->cmd_pos)
	{
		if (dup2(pipe->fd[1], 1) == -1)
			ms_fd_error(2, pipe);
	}
	if (pipe->out_fd != NULL)
	{
		if (init_outfile(pipe))
			exit(1);
	}
	close (pipe->fd[0]);
}

void	parent(t_pipe *pipe)
{
	// 	err = 0;
	// waitpid(pipe->pid, &err, 0);
	// error_code(&err);
	waitpid(pipe->pid, &pipe->status, 0);
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}


t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
{
	if (!tmp)
	{
		ms_fd_error(258, data);
		return (NULL);
	}
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
			ms_fd_error(258, data);
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
			tmp = skip_redir(tmp, data, redir_type);
			if (tmp == NULL)
				return (NULL);
		}
		else
		{
			cmd_line = add_quote_char(cmd_line, tmp);
			cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
			if (tmp->type != ASSIGN && tmp->type != STR_DQUOTES && tmp->type != STR_SQUOTES
				&& tmp->type != WORD && (!tmp->next || tmp->next->type != ASSIGN ))
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
	char	*cmd_line;
	t_token	**builtin_list;
	int		builtin_id;

	data->cmd_pos = count_pipes(pipes);
	i = 0;
	while (pipes[i])
	{
		builtin_id = 0;
		pipe(data->fd);
		check_value(pipes[i], *env, data);
		print_list(pipes[i]);
		cmd_line = get_cmd(pipes[i], data);
		data->parse.cmd = set_parse_cmd(pipes[i]);
		if (cmd_line)
		{
			builtin_list = read_tokens(cmd_line);
			builtin_list = merge_quoted_strings(builtin_list);
			builtin_id = is_builtin(cmd_line);
			if (builtin_id)
			{
				free(cmd_line);
				handle_builtinstr(*builtin_list, data, i, env, builtin_id);
			}
			else if (cmd_line && cmd_line[0])
			{
				free(cmd_line);
				handle_command(data, &pipes[i], i, env);
			}
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
	data->error_code = WEXITSTATUS(data->status);
	if (error_code(NULL))
	{
		data->error_code = error_code(NULL);
		i = 0;
		error_code(&i);
	}
	return (data->status);
}

int	main_loop(t_dlist **env, int stdin_restore, int stdout_restore, t_pipe *data)
{
	int				err;
	char			*inpt;
	t_token			**list;
	t_token			**pipes;

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
	if (parse(list, data))
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
			err = handle_input(pipes, data, env);
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
	t_pipe	data;

	if (argc != 1)
		return (1);
	l_envp = init_minishell(envp);
	(void) argv; //to silence unused argv error and not use dislay env
	stdin_restore = dup(0);
	stdout_restore = dup(1);
	data.error_code = 0;
	while (1)
		main_loop(l_envp, stdin_restore, stdout_restore, &data);
	return (argc);
}
