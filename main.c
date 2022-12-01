/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/01 17:59:11 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_splitenvp(t_parse parse, char **argv)
{
	int	i;

	i = 0;
	printf("%s envp parse: ", argv[0]);
	while (parse.split_envp[i])
		printf("%s\n", parse.split_envp[i++]);
}
void	init_path(t_token *list, char *cmdline, t_parse *parse)
{
	t_token	*tklist;

	tklist = list;
	parse->cmd = ft_split(cmdline, ' ');
	parse->path = get_path(parse->split_envp, parse->cmd[0]);
}
void	free_parse(t_parse *parse)
{
	free(parse->path);
	free_char_arr(parse->cmd);
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
}
void	child(t_pipe *pipe)
{
	// if (i < argc - 2)
	// {	
	// 	if (dup2(pipe->fd[1], 1) == -1)
	// 		fd_err(2);
	// }
	// pipe->parse.out_fd = NULL;
	// printf("1  out_fd = %s\n", pipe->out_fd);
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
		// printf("2  out_fd = %s\n", pipe->out_fd);
		// printf("str = %s\n", list->str);
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

void main_loop(int stdin_restore, t_pipe	data)
{
	char	*inpt;
	char	**inpt_split;
	t_token	**list;
	int		i;
	char	**envp_c;

	inpt = readline("Minishell$ ");
	if (!inpt)
		free_and_exit(SIGINT);
	inpt_split = ft_split(inpt, '|');

	if (inpt && inpt[0])
	{
		i = 0;
		while (inpt_split[i])
			i++;
		add_history(inpt);

		// char *args[2];
		// args[0] = "/bin/cat";
		// args[1] = "ps";
		//exec("/bin/cat", args, envp);
		//exec(NULL, NULL, envp);

		//printf("After check_value, printing list:\n");
		//print_list(*list);
		//handle_commandstr(list);

					// printf("%s\n", inpt);
			
	// 	printf("pos = %d\n", i);
		data.cmd_pos = i;
		i = 0;
		while (inpt_split[i])
		{
			list = read_tokens(inpt_split[i]);
			list = merge_quoted_strings(list);
			list = remove_empty(list); // deletes empty nodes
			envp_c = env_list_to_char_arr(g_env);
	// 		// for (int i = 0; envp[i]; i++) //  && ft_strncmp(envp[i], "", 1)
	// 		// 	printf("envp: %s\n", envp[i]);
			check_value(*list, envp_c);
			init_path(*list, get_cmd(*list, &data), &data.parse);
			data.pid = fork();
			dup2(stdin_restore, 1);
			if (data.pid == -1)
				fd_err(4);
			if (data.pid == 0)
			{
				child(&data, i);
				exec_cmd(&data, envp_c);
			}
			else
			{
				parent(&data);
				waitpid(0, &data.pid, 0);
			}
			free_char_arr(envp_c);
			free_token_list(list);
			free_parse(&data.parse);
			i++;
		}
	// 		// close(stdin_restore);
	}
	free(inpt);
	free_char_arr(inpt_split);
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	// t_parse	parse;
	int		stdin_restore;
	//int		stdout_restore;
	t_pipe	data;
	

	if (argc != 1)
		return (1);
	init_signals();
	data.parse.split_envp = envp_parse(envp);
	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env
	stdin_restore = dup(1);
	while (1)
	{
		dup2(stdin_restore, 0);
		dup2(stdout_restore, 1);
		main_loop(stdin_restore, data);
		close(stdin_restore);
		unlink("tmp");
	}
	free_and_close(&data);
	free_char_arr(data.parse.split_envp);
	return (argc);
}
