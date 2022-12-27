/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephanie.lakner <stephanie.lakner@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/12/26 13:36:37 by stephanie.l      ###   ########.fr       */
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

# define TOKENS " $'<>\""

int	g_stop;

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

t_token	*remove_spaces(t_token *list);
t_token	**remove_empty(t_token **list);

int		exec(char *program, char **args, char *const *envp);

/*command.c*/
//int		handle_commandstr(t_token **list);
int		handle_builtin(t_token *list, t_dlist **env, t_pipe *data);
int		handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env, int builtin_id);
int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env);


/*builtin.c*/
int		is_builtin(char *str);
int		exec_echo(t_token *token, t_dlist *env);
int		exec_cd(t_token *token, t_dlist *env);
int		exec_pwd(t_token *token, t_dlist *env);
int		exec_export(t_token *token, t_dlist *env);
int		exec_unset(t_token *token, t_dlist *env);
int		exec_env(t_token *token, t_dlist *env);
int		exec_exit(t_token *token, t_dlist **env);
int		builtin_plausible(t_token *token, char *builtin);
int		print_builtin_error(char *builtin, char *dir);

/*quotes.c*/
t_token	**merge_quoted_strings(t_token **list, t_pipe *data);
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

/* current main.c */
char	*get_cmd(t_token *list, t_pipe *data);
void	exec_cmd(t_pipe *pipe, t_dlist **env);
void	parent(t_pipe *pipe);
void	free_and_close(t_pipe *pipe);
int		init_outfile(t_pipe *pipe);
char** set_parse_cmd(t_token *head);

/*signals.c*/
void	signals_blocking_command(void);
void	heredoc_signals(int fd);



void	print_double_ptr(char **ptr);

#endif