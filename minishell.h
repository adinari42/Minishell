/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:49:44 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 16:34:52 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"

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
	// t_parse	parse;
	int		error_code;
	int		append;
}				t_pipe;

typedef struct s_token
{
	char			*str;
	int				type;
	int				id;
	char			*path;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef	struct s_expand
{
	int		i;
	int		j;
	int		k;
}				t_expand;

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
t_token	**merge_quoted_strings(t_token **list);
t_token	*merge_tokens(t_token *first, t_token *last);
t_token	*merge_two_tokens(t_token *token1, t_token *token2);
/*execute_line.c*/
void	execute_line(t_token *list, t_parse parse, char **envp);
void	init_path(t_token *tklist, t_parse parse);
char	*get_path(char **string, char *cmd);

#endif