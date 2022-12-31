/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/12/31 02:23:15 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include "../libft/libft.h"
# include "free.h"
# include "expand.h"
# include "llist.h"
# include "env.h"
# include "init.h"
# include "exec.h"
# include "string_utils.h"
# include <termios.h>
# include "../gnl/get_next_line.h"
# include "pipes.h"
# include <fcntl.h>
# include "parse.h"
# include "builtins.h"
# include "error.h"
# include "signals.h"
# include "command.h"
# include "tokens.h"
# include "input.h"

# define TOKENS " $'<>\""

extern volatile sig_atomic_t	g_stop;

enum e_tokentype
{
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	APPEND_IN,
	APPEND_OUT,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	ASSIGN,
	SPACE_TKN,
	WORD,
	STR_DQUOTES,
	STR_SQUOTES,
	INFILE,
	OUTFILE
};

enum e_builtins
{
	ECHO42,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};


/*quotes.c*/
t_token	**merge_quoted_strings(t_token **list);
t_token	*merge_tokens(t_token *first, t_token *last);
t_token	*merge_two_tokens(t_token *token1, t_token *token2);
char	*add_quote_char(char *cmd, t_token *tkn);

/*exit.c*/
void	free_and_exit(int signum, t_dlist **env);
void	exit_with_value(int retval, t_dlist **env);

/*execute_line.c*/
void	execute_line(t_token *list, t_parse parse, char **envp);
void	init_path(t_token **cmdline, t_parse *parse, t_dlist **env, t_pipe *data);
char	*get_path(char **string, char *cmd);
void	ms_fd_error(int i, t_pipe *data);
/*******/
t_token	*token_new(char *str);
void	delete(t_token *del_elem);
void	append(t_token **token, t_token *new_elem);
t_token	*list_end(t_token **token);
t_token	*list_start(t_token **token);

/* spaces.c */
t_token	*skip_spaces(t_token *token);
t_token	*skip_empty(t_token *token);
t_token	**tabs_to_spaces(t_token **pipes);

/* current main.c */
int		handle_single_pipe(t_token *plist, t_pipe *data, t_dlist **env, int i);
char	*get_cmd(t_token *list, t_pipe *data);
void	exec_cmd(t_pipe *pipe, t_dlist **env);
void	parent(t_pipe *pipe);
void	free_and_close(t_pipe *pipe);
int		init_outfile(t_pipe *pipe);
char	**set_parse_cmd(t_token *head);

/*init_infile.c*/
int		init_infile(t_token *list, t_pipe *data, int redir_type);
int		init_here_doc(t_token *list, t_pipe *pipe);
int		init_outfile(t_pipe *pipe);
/*init_fd_utils.c*/
int		open_tmp(t_pipe *pipe);
void	read_to_tmp(t_token *list, t_pipe *pipe, char	*str);
int		redir_in(t_token *list, t_pipe *data);
int		append_in(t_token *list, t_pipe *data);

/*command.c*/
void	treat_cmdline(t_token	*plist, t_pipe	*data, t_dlist	**env, int i);

/*cmd_param.c*/
void	init_path(t_token **cmd, t_parse *parse, t_dlist **env, t_pipe *data);
char**	set_parse_cmd(t_token *head);
char	*get_cmd(t_token *list, t_pipe *data);
t_token	*skip_redir(t_token *tmp, t_pipe *data, int redir_type);


char	*add_quote_char(char *cmd, t_token *tkn);

/*fork_and_exec.c*/
void	exec_cmd(t_pipe *data, t_dlist **env);
void	child(t_pipe *plist, int i);
void	parent(t_pipe *plist);

#endif