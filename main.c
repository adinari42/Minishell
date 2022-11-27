/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/11/27 17:50:34 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**envp_parse(char **envp)
// {
// 	int		j;
// 	char	**envp_parse;

// 	j = -1;
// 	while (envp[++j])
// 	{
// 		if (!ft_strncmp(envp[j], "PATH=", 5))
// 			break ;
// 	}
// 	envp_parse = ft_split(*(envp + j) + 5, ':');
// 	return (envp_parse);
// }

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
	// printf("full_cmd = %s\n", cmdline);
	// free(full_cmd);
	parse->cmd = ft_split(cmdline, ' ');
	parse->path = get_path(parse->split_envp, parse->cmd[0]);
}
void	free_parse(t_parse *parse)
{
	free(parse->path);
	free_2d(&parse->cmd);
}

// void	child(char *argv[], int argc, int i, t_pipe *pipe)
// {
// 	if (i < argc - 2)
// 	{	
// 		if (dup2(pipe->fd[1], 1) == -1)
// 			fd_err(2);
// 	}
// 	if (i == argc - 2)
// 		init_outfile(argv, argc, pipe);
// 	close (pipe->fd[0]);
// }
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

void	init_infile(t_token *list, t_pipe *pipe, int redir_type)
{
	t_token *tmp;

	tmp = list;
	// if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	// {
	// 	argc_err(argc, 6, pipe);
	// 	return (init_here_doc(argv, pipe));
	// }
	// else
	// {
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
			;
		}
		else if (redir_type == REDIR_OUT)
		{
			;
		}
}

t_token	*skip_redir(t_token *tmp, t_pipe data, int redir_type)
{
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == STR_DQUOTES || tmp->type == STR_SQUOTES)
		{
			init_infile(tmp, &data, redir_type);
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

char	*get_cmd(t_token *list, t_pipe data)
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
			printf("tmp = %s\n", tmp->str);
			tmp = tmp->next;
			tmp = skip_redir(tmp, data, redir_type);//break ;
			// if (tmp == NULL)
			// 	fd_err(5);
		}
		else	
		{
			printf("tmp = %s\n", tmp->str);
			cmd_line = ft_strjoin(cmd_line, tmp->str);
			cmd_line = ft_strjoin(cmd_line, " ");
			tmp = tmp->next;
		}
	}
	// printf("cmdline = %s \n", cmd_line);
	return (cmd_line);
}
void	free_and_close(t_pipe *pipe)
{
	free_2d(&pipe->parse.split_envp);
	// close(pipe->fd[0]);
	// close(pipe->fd[1]);
	unlink("tmp");
}
int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	char	**inpt_split;
	// t_parse	parse;
	t_token	**list;
	int		i;
	t_pipe	data;
	
	if (argc != 1)
		return (1);
	init_signals();
	data.parse.split_envp = envp_parse(envp);
	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env
	// display_splitenvp(parse, argv);
	while (1)
	{
		// dup2(0, 0);
		dup2(1, 0);
		// close(data.file.infile);
		inpt = readline("Minishell$ ");
		if (inpt && inpt[0])
		{
			add_history(inpt);
			printf("%s\n", inpt);
			// write(stdin_restore, inpt, ft_strlen(inpt));
			inpt_split = ft_split(inpt, '|');
			// printf("intsplit[0] = %s\n", inpt_split[0]);
			free(inpt);
			i = 0;
			while(inpt_split[i])
			{
				list = read_tokens(inpt_split[i]);
				list = merge_quoted_strings(list);
				// printf("token node = %s\n", *list.str);
				check_value(*list, envp);
				// printf("%d--------:\n", i);
				pipe(data.fd);
				// if (i == 0)
				// 	i = init_infile(argv, argc, &pip);
				// printf("printing list :\n");
				print_list(*list);
				init_path(*list, get_cmd(*list, data), &data.parse);
				// int j = -1;//display parse.cmd and parse.path
				/***********************************************/
				data.pid = fork();
				if (data.pid == -1)
					fd_err(4);
				if (data.pid == 0)
				{
					// child(argv, argc, i, &pip);
					exec_cmd(&data, envp);
				}
				else
				{
					waitpid(0, &data.pid, 0);
				}
				/***********************************************/
				free_token_list(list);
				free_parse(&data.parse);
				i++;
			}
		}
		free_2d(&inpt_split);
		unlink("tmp");
		// free_and_close(&data);
		
		// exit(1);
		// system("leaks minishell");
	}
	free_2d(&data.parse.split_envp);
	return (argc);
}
