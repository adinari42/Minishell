/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/27 16:38:47 by adinari          ###   ########.fr       */
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

void	display_splitenvp(t_parse parse, char **argv)
{
	int	i;

	i = 0;
	printf("%s envp parse: ", argv[0]);
	while (parse.split_envp[i])
		printf("%s\n", parse.split_envp[i++]);
}

	tklist = list;
	parse->cmd = ft_split(cmdline, ' ');
	parse->path = get_path(parse->split_envp, parse->cmd[0]);
}
void	free_parse(t_parse *parse)
{
	// char	**envp;

	envp = env_list_to_char_arr(g_env);
	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
		ms_fd_err(3);
}

void	exec_cmd(t_pipe *pipe, char *envp[])
{
	if (execve(pipe->parse.path, pipe->parse.cmd, envp) == -1)
		fd_err(3);
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
	pipe->append = 0;
	if (pipe->file.outfile == -1)
		fd_err(1);
	if (dup2(pipe->file.outfile, 1) == -1)
		fd_err(2);
	close (pipe->file.outfile);
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
		init_outfile(pipe);
	}
	close (pipe->fd[0]);
}
void	init_infile(t_token *list, t_pipe *pipe, int redir_type)
{
	wait(&pipe->pid);
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}


int	init_infile(t_token *list, t_pipe *data, int redir_type)
{
		data->out_fd = NULL;
		if (redir_type == APPEND_IN)
			init_here_doc(list, pipe);
		else if (redir_type == REDIR_IN)
		{
			write (2, "qwer", 4);
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
		}
		else	
		{
			cmd_line = ft_strjoin(cmd_line, tmp->str);
			cmd_line = ft_strjoin(cmd_line, " ");
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
void	parent(t_pipe *pipe)
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
		if (cmd_line)
		{
			builtin_list = read_tokens(cmd_line);
			builtin_list = merge_quoted_strings(builtin_list, data);
			builtin_list = remove_empty(builtin_list);
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
				handle_builtin(*builtin_list, env);
			}
			else if (cmd_line && cmd_line[0])
				handle_command(data, cmd_line, i, env);
			else if (cmd_line)
				free(cmd_line);
			free_token_list(*builtin_list);
			free(builtin_list);
		}
		else
			parent(data);
		i++;
	}
	status = 0;
	while (i--) 
	{
		waitpid(-1, &status, 0);
		data->error_code = WEXITSTATUS(status);
	}
	// write_exit_to_env(data->error_code);
	// printf("Child process exited with code: %d\n", WEXITSTATUS(status));
	return (status);
}

int	handle_input(char **inpt_split, t_pipe *data, char **envp, int stdout_restore)
{
	int		i;
	int		err;
	t_token	**list;
	// char	*cmd_line;
	// t_token	**builtin_list;
	(void) envp;
	(void) stdout_restore;

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
	list = merge_quoted_strings(list, &data);
	data.error_code = 0;
	if (!parse(*list, &data))
	{
		pipes = list_to_pipes(list);
		if (pipes && inpt && inpt[0] && !err)
		{
			free(inpt);
			signals_blocking_command();
			err = handle_input(pipes, &data, env);
		}
		else
			free(inpt);
		free_pipes(pipes);
	}
	else
	{
		free(inpt);
		free_token_list(*list);
		free(list);
	}
	return (err);
}

int	main(int argc, char **argv, char **envp)
{
	int		stdin_restore;
	//int		stdout_restore;
	t_pipe	data;
	char	*inpt;
	char	**inpt_split;
	t_parse	parse;
	t_token	**list;
	int		i;

	tmp = tokens;
	while(tmp)
	{
		printf(">%s\n", tmp->token);
		tmp = tmp->next;
	}
}

void	free_ll(t_tokens *stack)
{
	// t_parse	parse;
	int		stdin_restore;
	int		stdout_restore;
	int	err;

	tmp = stack;
	tmp1 = NULL;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
	stack = NULL;
}

void	free_2d(char ***to_free)
{
	size_t	i;

	i = 0;
	if (*to_free == NULL)
		return ;
	while ((*to_free)[i] != NULL)
	{
		free((*to_free)[i]);
		++i;
	}
	free(*to_free);
	*to_free = NULL;
}
int	push(t_tokens **thestack, char *thevalue)
{
	t_tokens	*newnode;
	t_tokens	*temp;

	temp = NULL;
	newnode = malloc(sizeof(t_tokens));
	if (newnode == NULL)
	{
		write(2, "Error\n", 6);
		free(newnode);
		return (0);
	}
	newnode->token = thevalue;
	newnode->next = NULL;
	if (*thestack == NULL)
		*thestack = newnode;
	else
	{
		temp = *thestack;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (1);
}

void	quote_tokens(t_tokens *tokens, char* line) {

    // const char *line = "'foobar'|cat'mousebar'sum";
    char	delim[2] = "\'\"";
    char	*p;
	char 	*first;
	char 	*second;
	char	*str;
	// char	c;
	int	j = 0;
	size_t len;
	int i = 0;
		p = line;
	
		first = NULL;
		second = NULL;
		len = -1;
		while (p && *p) /* for each char in line */
		{   i = 0;
			while (delim[i] && !first)
			{
				if (*p == delim[i])
					j = i;
				i++;
			}
			if (!first && *p == delim[j])             /* find 1st delim */
			{
				first = p;
				first++;                   /* set start ptr  */
			}	
			else if (!second && *p == delim[j])        /* find 2nd delim */
			{
				str = ft_substr(first, 0, len);   
				len = -1;                    /* set end ptr    */
				second = p;
			}
			if (first && second) {                     /* if both set    */
				push(&tokens, str);
				first = NULL;
				second = NULL;
			}
			if (first)
				len++;
			p++;
		}
	}



int main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_parse	parse;

	
	if (argc != 1)
		return (1);
	err = 0;
	init_minishell(envp);
	(void) argv; //to silence unused argv error and not use dislay env 
	data.parse.split_envp = envp_parse(envp);
	stdin_restore = dup(0);		// save original stdin/stdout
	stdout_restore = dup(1);
	//list = malloc(sizeof(t_token *));
	while (1)
	{
		// if (err == 1)
		// 	printf("Minishell$ ");
		dup2(stdin_restore, 0);
		dup2(stdout_restore, 1);
		// write(2, "i get here", 10);
		// close(stdin_restore);
		// close(stdout_restore);
		inpt = readline("Minishell$ ");
		add_history(inpt);
		inpt_split = ft_split(inpt, '|');
		free(inpt);
		if (inpt && inpt[0])
			err = handle_input(inpt_split, &data);

		dup2(stdin_restore, 0);
		dup2(stdout_restore, 1);
		if (inpt)
			free(inpt);
		free_char_arr(inpt_split);
		// dprintf(2, "fuck\n");
		// exit(1);
	}
	return (argc);
}