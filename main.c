/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephanie.lakner <stephanie.lakner@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/11/30 21:24:35 by adinari          ###   ########.fr       */
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

	tklist = list;
	parse->cmd = ft_split(cmdline, ' ');
	parse->path = get_path(parse->split_envp, parse->cmd[0]);
}
void	free_parse(t_parse *parse)
{
	free(parse->path);
	free_2d(&parse->cmd);
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
	// printf("i = %d, cmd_pos = %d\n", i, pipe->cmd_pos);
	if (i != pipe->cmd_pos)
	{	
		if (dup2(pipe->fd[1], 1) == -1)
			fd_err(2);
	}
	if (pipe->out_fd != NULL)
	{
		init_outfile(pipe);
	}
	close (pipe->fd[0]);
}
void	init_infile(t_token *list, t_pipe *pipe, int redir_type)
{
		if (pipe->out_fd)
			free(pipe->out_fd);
		pipe->out_fd = NULL;
		// printf("2  out_fd = %s\n", pipe->out_fd);
		// printf("str = %s\n", list->str);
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

// char	*get_cmd(t_token *list, t_pipe *data)
// {
// 	t_token *tmp;
// 	char	*cmd_line;
// 	int		redir_type;

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*inpt;
// 	char	**inpt_split;
// 	t_parse	parse;
// 	t_token	**list;
// 	int		i;

// 	if (argc != 1)
// 		return (1);
// 	init_signals();
// 	parse.split_envp = envp_parse(envp);
// 	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env
// 	// display_splitenvp(parse, argv);
// 	while (1)
// 	{
// 		inpt = readline("Minishell$ ");
// 		if (inpt && inpt[0])
// 		{
// 			add_history(inpt);
// 			printf("%s\n", inpt);
// 			inpt_split = ft_split(inpt, '|');
// 			free(inpt);
// 			i = 0;
// 			while(inpt_split[i])
// 			{
// 				list = read_tokens(inpt_split[i]);
// 				list = merge_quoted_strings(list);
// 				check_value(*list, envp);
// 				printf("1--------:\n");
// 				set_cmd_path(*list, parse);
// 				printf("printing list :\n");
// 				print_list(*list);
// 				// execute_line(*list, parse, envp);
// 				free_token_list(list);
// 				sleep(1);
// 				i++;
// 			}
// 		}
// 		free_2d(&inpt_split);
// 		// exit(1);
// 		// system("leaks minishell");
// 	}
// 	return (argc);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*inpt;
// 	//t_parse	parse;
// 	t_token	**list;
// 	char	**envp_c;
// 	tmp = list;
// 	cmd_line = ft_strdup("");
// 	while (tmp)
// 	{
// 		if (tmp->type == APPEND_IN || tmp->type == APPEND_OUT || tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
// 		{
// 			redir_type = tmp->type;
// 			tmp = tmp->next;
// 			tmp = skip_redir(tmp, data, redir_type);//break ;
// 		}
// 		else	
// 		{
// 			cmd_line = ft_strjoin(cmd_line, tmp->str);
// 			cmd_line = ft_strjoin(cmd_line, " ");
// 			tmp = tmp->next;
// 		}
// 	}
// 	return (cmd_line);
// }

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
	dup2(pipe->fd[0], 0);
	close (pipe->fd[1]);
}

void main_loop(int stdin_restore, t_pipe	data)
{
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
	init_signals();
	//(void) envp;
	init_env_llist(envp);
	//parse.split_envp = envp_parse(envp);
	(void) argv;//to silence unused argv error and not use dislay env 
	//display_splitenvp(parse, argv);
	while (1)
	{
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
		{
			i = 0;
			while (inpt_split[i])
				i++;
			data.cmd_pos = i;
			i = 0;
			while(inpt_split[i])
			{
				pipe(data.fd);
				list = read_tokens(inpt_split[i]);
				list = merge_quoted_strings(list);
				check_value(*list, envp);
				init_path(*list, get_cmd(*list, &data), &data.parse);
				/***********************************************/
				data.pid = fork();
				if (data.pid == -1)
					fd_err(4);
				if (data.pid == 0)
				{
					child(&data, i + 1);
					exec_cmd(&data, envp);
				}
				else
				{
					parent(&data);	
					waitpid(data.pid, &err, 0);
				}
				/***********************************************/
				free_token_list(list);
				free_parse(&data.parse);
				i++;
			}
			//for each pipe
					//waitpid(0, &data.pid, 0);
		}
		free_2d(&inpt_split);
		unlink("tmp");
		// exit(1);
		// system("leaks minishell");
	}
	return (argc);
}