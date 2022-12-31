/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 01:18:22 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

volatile sig_atomic_t	g_stop;

void	init_path(t_token **cmd, t_parse *parse, t_dlist **env, t_pipe *data)
{
	char	*var_path;
	char	**split_path;

	parse->cmd = set_parse_cmd(*cmd);
	var_path = expand_var_in_str(*env, "PATH", data);
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

void	child(t_pipe *plist, int i)
{
	if (i < plist->cmd_pos)
	{
		if (dup2(plist->fd[1], 1) == -1)
			ms_fd_error(2, plist);
	}
	if (plist->out_fd != NULL)
	{
		if (init_outfile(plist))
			exit(1);
	}
	close (plist->fd[0]);
}

void	parent(t_pipe *plist)
{
	waitpid(plist->pid, &plist->status, 0);
	dup2(plist->fd[0], 0);
	close (plist->fd[1]);
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

char	*join_param(char *cmd_line, t_token *tmp)
{
	cmd_line = add_quote_char(cmd_line, tmp);
	cmd_line = ft_strjoin_free_str1(cmd_line, tmp->str);
	// if (tmp->type != ASSIGN && tmp->type != STR_DQUOTES && tmp->type != STR_SQUOTES
	// 	&& tmp->type != WORD && (!tmp->next || tmp->next->type != ASSIGN ))
	// 	cmd_line = ft_strjoin_free_str1(cmd_line, " ");
	cmd_line = add_quote_char(cmd_line, tmp);
	return (cmd_line);
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
			{
				free(cmd_line);
				return (NULL);
			}
		}
		else
			cmd_line = join_param(cmd_line, tmp);
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

void	free_and_close(t_pipe *plist)
{
	close(plist->fd[0]);
	close(plist->fd[1]);
	unlink("tmp");
}

void call_cmdline(t_token *plist, t_dlist **env, t_pipe *data, int i)
{
	char	*cmd_line;
	t_token	**builtin_list;

	cmd_line = get_cmd(plist, data);
	data->parse.cmd = set_parse_cmd(plist);
	if (cmd_line)
	{
		builtin_list = tokenize(cmd_line);
		if (is_builtin(cmd_line) && !g_stop)
		{
			free(cmd_line);
			data->error_code = handle_builtinstr(*builtin_list, data, i, env);
			error_code(&data->error_code);
		}
		else if (cmd_line && cmd_line[0] && !g_stop)
		{
			free(cmd_line);
			handle_command(data, &plist, i, env);
		}
		else if (cmd_line)
			free(cmd_line);
		free_token_list_and_ptr(builtin_list);
	}
	else
		parent(data);
}

int	handle_single_pipe(t_token *plist, t_pipe *data, t_dlist **env, int i)
{
	g_stop = 0;
	pipe(data->fd);
	check_value(plist, *env, data);
	call_cmdline(plist, env, data, i);
	free(data->parse.cmd);
	unlink("tmp");
	return (0);
}

void	main_loop(t_dlist **env, int stdin_rstr, int stdout_rstr, t_pipe *data)
{
	char			*inpt;
	t_token			**list;
	t_token			**plist;

	dup2(stdin_rstr, 0);
	dup2(stdout_rstr, 1);
	reset_term_signals();
	inpt = get_input_line(env, data, stdin_rstr);
	list = read_tokens(inpt);
	free(inpt);
	if (parse(list, data))
		free_token_list_and_ptr(list);
	else
	{
		plist = list_to_pipes(list);
		plist = tabs_to_spaces(plist);
		if (plist)
		{
			signals_blocking_command();
			handle_input(plist, data, env);
		}
		free_pipes(plist);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_dlist			**l_envp;
	int				stdin_restore;
	int				stdout_restore;
	t_pipe			data;

	if (argc != 1)
		return (1);
	l_envp = init_minishell(envp);
	(void) argv;
	stdin_restore = dup(0);
	stdout_restore = dup(1);
	data.error_code = 0;
	while (1)
		main_loop(l_envp, stdin_restore, stdout_restore, &data);
	return (argc);
}
