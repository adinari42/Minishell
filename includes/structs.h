/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:26:28 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 18:10:43 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_kval
{
	char	*key;
	char	*val;
}	t_kval;

typedef struct s_dlist
{
	struct s_kval	*content;
	struct s_dlist	*next;
}	t_dlist;

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
	char	*out_fd;
	int		cmd_pos;
	t_parse	parse;
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

typedef struct s_expand
{
	int		i;
	int		j;
	int		k;
}				t_expand;

#endif
