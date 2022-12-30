/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/12/30 19:27:21 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/wait.h>
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

static const char *const	g_builtins[] = {
	"echo",
	"cd",
	"pwd",
	"export",
	"unset",
	"env",
	"exit"
};

/*tokens.c*/
t_token	**read_tokens(char *bashcmd);
void	set_cmd_path(t_token *tklist, t_parse parse);
int		token_type(char *c);
void	print_list(t_token *tklist);
void	init_signals(void);

int		exec(char *program, char **args, char *const *envp);

/*command.c*/
//int		handle_commandstr(t_token **list);
int		handle_builtin(t_token *list, t_dlist **env, t_pipe *data);
int		handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env, int builtin_id);
int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env);




/*quotes.c*/
t_token	**merge_quoted_strings(t_token **list);
t_token	*merge_tokens(t_token *first, t_token *last);
t_token	*merge_two_tokens(t_token *token1, t_token *token2);

/*exit.c*/
void	free_and_exit(int signum, t_dlist **env);
void	exit_with_value(int retval, t_dlist **env);

/*execute_line.c*/
void	execute_line(t_token *list, t_parse parse, char **envp);
void	init_path(t_token **cmdline, t_parse *parse, t_dlist **env, t_pipe *data);
char	*get_path(char **string, char *cmd);
void	ms_fd_err(int i);
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

/* current main.c */
char	*get_cmd(t_token *list, t_pipe *data);
void	exec_cmd(t_pipe *pipe, t_dlist **env);
void	parent(t_pipe *pipe);
void	free_and_close(t_pipe *pipe);
int		init_outfile(t_pipe *pipe);
char	**set_parse_cmd(t_token *head);

/*signals.c*/
int		error_code(int *err);
void	signals_blocking_command(void);
void	heredoc_signals(int fd);

/*init_infile.c*/
int		init_infile(t_token *list, t_pipe *data, int redir_type);
int		init_here_doc(t_token *list, t_pipe *pipe);
int		init_outfile(t_pipe *pipe);
/*init_fd_utils.c*/
int		open_tmp(t_pipe *pipe);
void	read_to_tmp(t_token *list, t_pipe *pipe, char	*str);
int		redir_in(t_token *list, t_pipe *data);
int		append_in(t_token *list, t_pipe *data);

void	print_double_ptr(char **ptr);

#endif