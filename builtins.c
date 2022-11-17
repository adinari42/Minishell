/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/17 21:56:15 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtins)
		/sizeof(const char *const))
	{
		if (!ft_strncmp(str, g_builtins[i], ft_strlen(g_builtins[i] + 1)))
			return (1);
		i++;
	}
	return (0);
}

int	exec_echo(t_token **list)
{
	t_token	*token;
	int		ret;
	int		newline;

	token = list_start(list);
	ret = 0;
	newline = 1;
	if (ft_strncmp(token->str, "echo", 5))
	{
		printf("Something went wrong here, %s is not the echo command\n",
			token->str);
		return (1);
	}
	if (token->next && !ft_strncmp(token->next->str, "-n", 3))
		newline = 0;
	while (token->next)
	{
		token = token->next;
		write(1, token->str, ft_strlen(token->str));
	}
	if (newline)
		printf("\n");
	return (ret);
}

// these functions are emtpy dummy functions for now so it compiles
int	exec_cd(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_export(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_unset(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_env(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_exit(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_pwd(t_token **list)
{
	t_token	*token;
	char	buf[1024];

	token = list_start(list);
	if (ft_strncmp(token->str, "pwd", 4))
	{
		printf("Something went wrong here, %s is not the pwd command\n",
			token->str);
		return (1);
	}
	while (token->next)
	{
		token = token->next;
		if (token->type != SPACE)
		{
			printf("pwd: too many arguments");
			return (1);
		}
	}
	getcwd(buf, 1024);
	printf("%s \n", buf);
	return (0);
}

