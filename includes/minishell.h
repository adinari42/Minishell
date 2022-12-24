/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/12/24 04:42:38 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# include "../gnl/get_next_line.h"
# include "pipes.h"
# include <fcntl.h>
# include "parse.h"

# define TOKENS " $'<>\""

//char	**g_envp;
t_dlist	**g_env;

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
	SPACE,
	WORD,
	STR_DQUOTES,
	STR_SQUOTES
};

enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
};

const static char *const	g_builtins[] = {
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
int		token_type(char *c);

void	init_signals(void);

int		exec(char *program, char **args, char *const *envp);

/*command.c*/
int		handle_commandstr(t_token **list);
int		handle_builtin(t_token **list);
int		handle_command(t_token **list);

/*builtin.c*/
int		is_builtin(char *str);
int		exec_echo(t_token **token);
int		exec_cd(t_token **token);
int		exec_pwd(t_token **token);
int		exec_export(t_token **token);
int		exec_unset(t_token **token);
int		exec_env(t_token **token);
int		exec_exit(t_token **token);
int		builtin_plausible(t_token *token, char *builtin);
int		print_builtin_error(char *builtin, char *dir);

/*quotes.c*/
t_token	**merge_quoted_strings(t_token **list, t_pipe *data);
t_token	*merge_tokens(t_token *first, t_token *last);
t_token	*merge_two_tokens(t_token *token1, t_token *token2);

/*exit.c*/
void	free_globals(void);
void	free_and_exit(int signum);
void	exit_with_value(int retval);


/*execute_line.c*/
void	execute_line(t_token *list, t_parse parse, char **envp);
void	init_path(t_token *tklist, t_parse parse);
char	*get_path(char **string, char *cmd);

t_token	**read_tokens(char *bashcmd);
void	set_cmd_path(t_token *tklist, t_parse parse);
int		token_type(char *c);
void	init_signals(void);
void	print_list(t_token *tklist);
t_token	*token_new(char *str);
void	free_token_list(t_token **list);
void	free_token(t_token *elem);
void	delete(t_token *del_elem);
void	append(t_token **token, t_token *new_elem);
t_token	*list_end(t_token **token);
t_token	*list_start(t_token **token);
/*expandvalue.c*/
char	*value_expand(char **envp, char *var);
char	*expand_value(char *str, char **envp);
void	check_value(t_token *list, char **envp);
void	free_2d(char ***to_free);
void	free_strings(char *str, char **split1);
char	*add_space(char *tmp, char *res);
char	*join_to_res(char *tmp, char **split2, char *res, int j, char **envp);
/*quotes.c*/
// t_token	**merge_quoted_strings(t_token **list);
// t_token	*merge_tokens(t_token *first, t_token *last);
// t_token	*merge_two_tokens(t_token *token1, t_token *token2);

/* spaces.c */
t_token	*skip_spaces(t_token *token);

#endif