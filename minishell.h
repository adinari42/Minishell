/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/11/17 21:07:26 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define TOKENS " $'<>\""

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

typedef struct s_history
{
	char				*history;
	struct s_history	*next;
}				t_history;

typedef struct file
{
	int	infile;
	int	outfile;
	int	tmp;
}				t_file;

typedef struct parse
{
	char	**cmd;
	char	**split_envp;
	char	*path;
}				t_parse;

typedef struct pipe
{
	int		fd[2];
	pid_t	pid;
	t_file	file;
	t_parse	parse;
	int		error_code;
	int		append;
}				t_pipe;

typedef struct s_token
{
	char			*str;
	int				type;
	int				id;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

t_token	**read_tokens(char *bashcmd);
int		token_type(char *c);
void	init_signals(void);

t_token	*token_new(char *str);
void	free_token_list(t_token **list);
void	free_token(t_token *elem);
void	delete(t_token *del_elem);
void	append(t_token **token, t_token *new_elem);
t_token	*list_start(t_token **token);
t_token	*list_end(t_token **token);
void	print_list(t_token *tklist);
t_token	**merge_quoted_strings(t_token **list);
t_token	*merge_tokens(t_token *first, t_token *last);
t_token	*merge_two_tokens(t_token *first, t_token *last);

t_token	**remove_spaces(t_token **list);

int		exec(char *program, char **args, char *const *envp);

int		handle_commandstr(t_token **list);
int		handle_builtin(t_token **list);
int		handle_command(t_token **list);

int		is_builtin(char *str);
int		exec_echo(t_token **token);
int		exec_cd(t_token **token);
int		exec_pwd(t_token **token);
int		exec_export(t_token **token);
int		exec_unset(t_token **token);
int		exec_env(t_token **token);
int		exec_exit(t_token **token);

#endif