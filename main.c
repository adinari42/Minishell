/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephanie.lakner <stephanie.lakner@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/20 18:03:31 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_parse(char **envp)
{
	int		j;
	char	**envp_parse;

	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], "PATH=", 5))
			break ;
	}
	envp_parse = ft_split(*(envp + j) + 5, ':');
	return (envp_parse);
}

void	display_splitenvp(t_parse parse, char **argv)
{
	int	i;

	i = 0;
	printf("%s envp parse: ", argv[0]);
	while (parse.split_envp[i])
		printf("%s\n", parse.split_envp[i++]);
}

void	display_list(t_tokens *tokens)
{
	char	*inpt;
	t_parse	parse;
	t_token	**list;

	tmp = tokens;
	while(tmp)
	{
		printf(">%s\n", tmp->token);
		tmp = tmp->next;
	}
}

void	free_ll(t_tokens *stack)
{
	t_tokens	*tmp1;
	t_tokens 	*tmp;

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
	init_signals();
	init_env_llist(envp);
	parse.split_envp = envp_parse(envp);
	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env 
	//g_envp = envp;
	display_splitenvp(parse, argv);
	while (1)
	{
		inpt = readline("Minishell$ ");
		if(inpt && inpt[0])
			add_history(inpt);
			printf("%s\n", inpt);
			list = read_tokens(inpt);
			list = merge_quoted_strings(list);
			printf("After quotes treatment: \n");
			print_list(*list);
			printf("After removing spaces: \n");
			list = remove_spaces(list);
			print_list(*list);
			// char *args[2];
			// args[0] = "/bin/cat";
			// args[1] = "ps";
			// exec("/bin/cat", args, envp);

			//exec(NULL, NULL, envp);
			
			//system("leaks minishell");
			// printf("After quotes treatment: \n");
			// print_list(*list);
			// printf("After removing spaces: \n");
			check_value(*list, envp);
			// we need a function here that deletes empty nodes
			list = remove_empty(list);
			printf("After check_value, printing list:\n");
			print_list(*list);
			handle_commandstr(list);
			if (inpt)
				free(inpt);
			free_token_list(list);
		}
		if (inpt)
			free(inpt);
		//system("leaks minishell");
	}
	return (argc);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	t_dlist	**l_envp;
// 	int		stdin_restore;
// 	int		stdout_restore;

// 	if (argc != 1)
// 		return (1);
// 	l_envp = init_minishell(envp);
// 	(void) argv; //to silence unused argv error and not use dislay env 
// 	stdin_restore = dup(0);		// save original stdin/stdout
// 	stdout_restore = dup(1);
// 	while (1)
// 		main_loop(l_envp, stdin_restore, stdout_restore);
// 	return (argc);
// }


// extern volatile int	g_stop;

// void	init_path(t_token **cmdline, t_parse *parse, t_dlist **env, t_pipe *data)
// {
// 	char	*var_path;
// 	char	**split_path;
// 	int		i;

// 	i = 0;
// 	parse->cmd = set_parse_cmd(*cmdline);
// 	var_path = get_value_from_key(*env, "PATH", data);
// 	split_path = ft_split(var_path, ':');
// 	parse->path = get_path(split_path, parse->cmd[0]);
// 	free_split(split_path);
// }

// void	exec_cmd(t_pipe *data, t_dlist **env)
// {
// 	char	**envp;

// 	envp = env_list_to_char_arr(env);
// 	if (!data->parse.path)
// 	{
// 		write(2, data->parse.cmd[0], ft_strlen(data->parse.cmd[0]));
// 		ms_fd_error(127, data);
// 		exit (127);
// 	}
// 	else
// 		execve(data->parse.path, data->parse.cmd, envp);
// 	// if (execve(data->parse.path, data->parse.cmd, envp) == -1)
// 	// 	ms_fd_error(3, data);
// 	free_char_arr(envp);
// 	exit(0);
// }

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

// // int	init_here_doc(t_token *list, t_pipe *pipe)
// // {
// // 	char	*str;

// // 	(void) list;
// // 	pipe->file.infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// // 	if (pipe->file.infile == -1)
// // 	{
// // 		ms_fd_error(1, pipe);
// // 		return (1);
// // 	}
// // 	pipe->file.tmp = open("tmp", O_RDONLY | O_CREAT);
// // 	if (pipe->file.infile == -1 || pipe->file.tmp == -1)
// // 	{
// // 		ms_fd_error(1, pipe);
// // 		return (1);
// // 	}
// // 	str = ft_strdup("");
// // 	reset_term_signals();
// // 	heredoc_signals(STDIN_FILENO);
// // 	g_stop = 0;
// // 	while (!g_stop && str)
// // 	{
// // 		str = readline("> ");
// // 		if (str && (!ft_strncmp(list->str, str, ft_strlen(str) + 1)))
// // 		{
// // 			free(str);
// // 			break ;
// // 		}
// // 		ft_putstr_fd(str, pipe->file.infile);
// // 		ft_putstr_fd("\n", pipe->file.infile);
// // 		if (str)
// // 			free(str);
// // 	}
// // 	signals_blocking_command();
// // 	pipe->append = 1;
// // 	if (dup2(pipe->file.tmp, 0) == -1)
// // 	{
// // 		ms_fd_error(2, pipe);
// // 		return (1);
// // 	}
// // 	close(pipe->file.infile);
// // 	close(pipe->file.tmp);
// // 	return (0);
// // }

// int	init_outfile(t_pipe *pipe)
// {
// 	if (pipe->append == 0)
// 		pipe->file.outfile = open(pipe->out_fd,
// 				O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	else
// 		pipe->file.outfile = open(pipe->out_fd,
// 				O_WRONLY | O_CREAT | O_APPEND, 0644);
// 	pipe->append = 0;
// 	if (pipe->file.outfile == -1)
// 	{
// 		ms_fd_error(1, pipe);
// 		return (1);
// 	}
// 	if (dup2(pipe->file.outfile, 1) == -1)
// 	{
// 		ms_fd_error(2, pipe);
// 		return (1);
// 	}
// 	close (pipe->file.outfile);
// 	return (0);
// }

// void	child(t_pipe *pipe, int i)
// {
// 	if (i != pipe->cmd_pos)
// 	{	
// 		if (dup2(pipe->fd[1], 1) == -1)
// 			ms_fd_err(2);
// 	}
// 	if (pipe->out_fd != NULL)
// 	{
// 		if (init_outfile(pipe))
// 			ms_fd_error(1, pipe);
// 	}
// 	close (pipe->fd[0]);
// }

// void	parent(t_pipe *pipe)
// {
// 	dup2(pipe->fd[0], 0);
// 	close (pipe->fd[1]);
// }

// int	init_infile(t_token *list, t_pipe *data, int redir_type)
// {
// 		data->out_fd = NULL;
// 		if (redir_type == APPEND_IN)
// 		{	
// 			if(init_here_doc(list, data))
// 				return(1);
// 		}
// 		else if (redir_type == REDIR_IN)
// 		{
// 			data->file.infile = open(list->str, O_RDONLY);
// 			if (data->file.infile == -1)
// 			{
// 				write(2, list->str, ft_strlen(list->str));
// 				close(data->file.infile);
// 				ms_fd_error(1, data);
// 				return (1);
// 			}
// 			dup2(data->file.infile, 0);
// 			close(data->file.infile);
// 		}
// 		else if (redir_type == APPEND_OUT)
// 		{
// 			data->append = 1;
// 			data->out_fd = list->str;
// 		}
// 		else if (redir_type == REDIR_OUT)
// 		{
// 			data->append = 0;
// 			data->out_fd = list->str;
// 		}
// 	return (0);
// }

// // int	init_infile(t_token *list, t_pipe *data, int redir_type)
// // {
// // 	data->out_fd = NULL;
// // 	if (redir_type == APPEND_IN)
// // 	{	
// // 		if (init_here_doc(list, data))
// // 			return (1);
// // 	}
// // 	else if (redir_type == REDIR_IN)
// // 	{
// // 		data->file.infile = open(list->str, O_RDONLY);
// // 		if (data->file.infile == -1)
// // 		{
// // 			write(2, list->str, ft_strlen(list->str));
// // 			close(data->file.infile);
// // 			ms_fd_error(1, data);
// // 			return (1);
// // 		}
// // 		dup2(data->file.infile, 0);
// // 		close(data->file.infile);
// // 	}
// // 	else if (redir_type == APPEND_OUT)
// // 	{
// // 		data->append = 1;
// // 		data->out_fd = list->str;
// // 	}
// // 	else if (redir_type == REDIR_OUT)
// // 	{
// // 		data->append = 0;
// // 		data->out_fd = list->str;
// // 	}
// // 	return (0);
// // }

// t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type)
// {
// 	while (tmp)
// 	{
// 		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
// 		{
// 			if (init_infile(tmp, data, redir_type) == 1)
// 				return (NULL);
// 			return (tmp);
// 		}
// 		else if (tmp->type == SPACE_TKN)
// 			tmp = tmp->next;
// 		else
// 		{
// 			ms_fd_error(5, data);
// 			break ;
// 		}
// 	}
// 	return (NULL);
// }

// char	*add_quote_char(char *cmd, t_token *tkn)
// {
// 	if (tkn->type == STR_DQUOTES)
// 		cmd = ft_strjoin_free_str1(cmd, "\"");
// 	else if (tkn->type == STR_SQUOTES)
// 		cmd = ft_strjoin_free_str1(cmd, "'");
// 	return (cmd);
// }

// char	*get_cmd(t_token *list, t_pipe *data)
// {
// 	t_token	*tmp;
// 	char	*cmd_line;
// 	int		redir_type;

// 	tmp = list;
// 	cmd_line = ft_strdup("");
// 	data->out_fd = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->type == APPEND_IN || tmp->type == APPEND_OUT || tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
// 		{
// 			redir_type = tmp->type;
// 			tmp = tmp->next;
// 			tmp = skip_redir(tmp, data, redir_type);//break ;
// 			if (tmp == NULL)
// 				return (NULL);
// 			tmp = tmp->next;
// 		}
// 		else
// 		{
// 			cmd_line = add_quote_char(cmd_line, tmp);
// 			cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
// 			if (tmp->type != ASSIGN && tmp->type != STR_DQUOTES && tmp->type != STR_SQUOTES
// 				&&  (!tmp->next || tmp->next->type != ASSIGN))
// 				cmd_line = ft_strjoin_free_str1(cmd_line, " ");
// 			cmd_line = add_quote_char(cmd_line, tmp);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (cmd_line);
// }
// char** set_parse_cmd(t_token *head)
// {
//  	int		count;
//     t_token	*curr;
//     char	**cmd;
	
// 	count = 0;
//     curr = head;
//     while (curr != NULL)
//     {
// 		if (curr->type == WORD || curr->type == STR_DQUOTES || curr->type == STR_SQUOTES)
// 			count++;
//         curr = curr->next;
//     }
//     cmd = (char**)malloc((count + 1) * sizeof(char*));
//     if (cmd == NULL)
//     {
//         perror("malloc");
//         exit(1);
//     }
//     count = 0;
//     curr = head;
//     while (curr != NULL)
//     {
// 		if (curr->type == WORD || curr->type == STR_DQUOTES || curr->type == STR_SQUOTES)
// 			cmd[count++] = curr->str;
// 		curr = curr->next;
//     }
// 	cmd[count] = NULL;
//     return cmd;
// }

// void	free_and_close(t_pipe *pipe)
// {
// 	close(pipe->fd[0]);
// 	close(pipe->fd[1]);
// 	unlink("tmp");
// }

// // int	handle_input(t_token **pipes, t_pipe *data, t_dlist **env)
// // {
// // 	int		i;
// // 	int		status;
// // 	char	*cmd_line;
// // 	t_token	**builtin_list;

// // 	data->cmd_pos = count_pipes(pipes);
// // 	i = 0;
// // 	status = 0;
// // 	while (pipes[i])
// // 	{
// // 		pipe(data->fd);
// // 		check_value(pipes[i], *env, data);
// // 		// printf("checkvalue: \n");
// // 		// print_list(pipes[i]);	
// // 		cmd_line = get_cmd(pipes[i], data);
// // 		// printf("cmd_line = %s.\n", cmd_line);
// // 		data->parse.cmd = set_parse_cmd(pipes[i]);
// // 		if (cmd_line)
// // 		{
// // 			builtin_list = read_tokens(cmd_line);
// // 			builtin_list = merge_quoted_strings(builtin_list);
// // 			//builtin_list = remove_empty(builtin_list);
// // 			if (is_builtin(cmd_line) == 1)
// // 			{
// // 				free(cmd_line);
// // 				handle_builtinstr(*builtin_list, data, i, env);
// // 			}
// // 			else if (is_builtin(cmd_line))
// // 			{
// // 				free(cmd_line);
// // 				if (data->out_fd != NULL)
// // 				{
// // 					if (init_outfile(data))
// // 						ms_fd_error(1, data);
// // 				}
// // 				handle_builtin(*builtin_list, env, data);
// // 			}
// // 			else if (cmd_line && cmd_line[0])
// // 				handle_command(data, &pipes[i], i, env);
// // 			else if (cmd_line)
// // 				free(cmd_line);
// // 			free_token_list(*builtin_list);
// // 			free(builtin_list);
// // 		}
// // 		else
// // 			parent(data);
// // 		i++;
// // 	}
// // 	status = 0;
// // 	waitpid(-1, &status, 0);
// // 	data->error_code = WEXITSTATUS(status);
// // 	return (status);
// // }

// int	handle_input(t_token **pipes, t_pipe *data, t_dlist **env)
// {
// 	int		i;
// 	int		status;
// 	char	*cmd_line;
// 	t_token	*builtin_list;

// 	data->cmd_pos = count_pipes(pipes);
// 	i = 0;
// 	while (pipes[i])
// 	{
// 		pipe(data->fd);
// 		// pipes[i] = merge_quoted_strings(pipes[i], data);
// 		// printf("pipes[i] merge: \n");
// 		// print_list(pipes[i]);
// 		if (pipes[i] == NULL)
// 			return (1);
// 		check_value(pipes[i], *env, data);
// 		// printf("pipes[i] checkvalue: \n");
// 		// print_list(pipes[i]);
// 		// printf("checkvalue: \n");
// 		// print_list(pipes[i]);	
// 		cmd_line = get_cmd(pipes[i], data);
// 		// printf("cmd_line = %s.\n", cmd_line);
// 		data->parse.cmd = set_parse_cmd(pipes[i]);
// 		if (cmd_line)
// 		{
// 			builtin_list = read_tokens(cmd_line);
// 			builtin_list = merge_quoted_strings(builtin_list, data);//, data);
// 			builtin_list = remove_empty(builtin_list);
// 			if (is_builtin(cmd_line) == 1)
// 				handle_builtinstr(builtin_list, data, i, env);
// 			else if (is_builtin(cmd_line))
// 			{
// 				if (data->out_fd != NULL)
// 				{
// 					if (init_outfile(data))
// 						ms_fd_error(1, data);
// 				}
// 				handle_builtin(builtin_list, env);
// 			}
// 			else if (cmd_line && cmd_line[0])
// 				handle_command(data, &pipes[i], i, env);
// 			free_token_list(builtin_list);
// 			free(cmd_line);
// 		}
// 		else
// 			parent(data);
// 		i++;
// 	}
// 	status = 0;
// 	waitpid(-1, &status, 0);
// 	data->error_code = WEXITSTATUS(status);
// 	return (status);
// }


// int	main_loop(t_dlist **env, int stdin_restore, int stdout_restore)
// {
// 	int		err;
// 	char	*inpt;
// 	t_token	*list;
// 	t_pipe	data;
// 	t_token	**pipes;	

// 	err = 1;
// 	dup2(stdin_restore, 0);
// 	dup2(stdout_restore, 1);
// 	inpt = readline("Minishell$ ");
// 	if (!inpt)
// 		free_and_exit(SIGINT, env);		// this does the exit on Ctrl-D
// 	add_history(inpt);
// 	list = read_tokens(inpt);
// 	list = merge_quoted_strings(list, &data); //, &data);
// 	pipes = list_to_pipes(list);
// 	if (pipes && inpt && inpt[0])
// 		err = handle_input(pipes, &data, env);
// 	free(inpt);
// 	free_pipes(pipes);
// 	return (err);
// }

// // int	main_loop(t_dlist **env, int stdin_restore, int stdout_restore)
// // {
// // 	int		err;
// // 	char	*inpt;
// // 	t_token	**list;
// // 	t_pipe	data;
// // 	t_token	**pipes;	
// // 	err = 0;
// // 	//data.error_code = 0;
// // 	dup2(stdin_restore, 0);
// // 	dup2(stdout_restore, 1);
// // 	reset_term_signals();
// // 	inpt = readline("Minishell$ ");
// // 	if (!inpt)
// // 		free_and_exit(SIGINT, env);		// this does the exit on Ctrl-D
// // 	add_history(inpt);
// // 	if (is_empty_inpt(inpt))
// // 		return (0);
// // 	list = read_tokens(inpt);
// // 	free(inpt);
// // 	//if (data.error_code || parse(list, &data))
// // 	if (parse(list, &data))
// // 	{
// // 		free_token_list(*list);
// // 		free(list);
// // 	}
// // 	else
// // 	{
// // 		pipes = list_to_pipes(list);
// // 		if (pipes && !err)
// // 		{
// // 			signals_blocking_command();
// // 			err = handle_input(pipes, &data, env);
// // 		}
// // 		free_pipes(pipes);
// // 	}
// // 	return (err);
// // }

// int	main(int argc, char **argv, char **envp)
// {
// 	t_dlist	**l_envp;
// 	int		stdin_restore;
// 	int		stdout_restore;

// 	if (argc != 1)
// 		return (1);
// 	l_envp = init_minishell(envp);
// 	(void) argv; //to silence unused argv error and not use dislay env 
// 	stdin_restore = dup(0);		// save original stdin/stdout
// 	stdout_restore = dup(1);
// 	while (1)
// 	{
// 		main_loop(l_envp, stdin_restore, stdout_restore);
// 		reset_term_signals();
// 	}
// 	return (argc);
// }
