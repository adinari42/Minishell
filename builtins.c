/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 14:47:45 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_envp;

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

// these functions are emtpy dummy functions for now so it compiles
int	exec_echo(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	newline = 1;
	if (ft_strncmp(token->str, "echo", 5))
	{
		printf("Something went wrong here, %s is not the echo command\n",
			token->str);
		return (1);
	}
	if (token->next && !ft_strncmp(token->next->str, "-n", 3))
	{
		token = token->next;
		newline = 0;
	}
	while (token->next)
	{
		token = token->next;
		write(1, token->str, ft_strlen(token->str));
	}
	if (newline)
		printf("\n");
	return (ret);
}

int	exec_cd(t_token **list)
{
	int	ret;

	token = list_start(list);
	dir_found = 0;
	if (ft_strncmp(token->str, "cd", 3))
	{
		printf("Something went wrong here, %s is not the cd command\n",
			token->str);
		return (1);
	}
	token = token->next;
	while (token->next)
	{
		token = token->next;
		if (token->type == WORD || token->type == STR_DQUOTES || token->type == STR_SQUOTES)
		{
			if (dir_found)
				printf("cd: string not in pwd: %s\n", list_start(list)->next->str);
			else
				dir_found = 1;
		}
	}
	ret = chdir(list_start(list)->next->str);
	if (ret == -1)
		printf("cd: no such file or directory: %s\n", list_start(list)->next->str);
	return (ret);
}

int	exec_export(t_token **list)
{
	int		ret;
	t_token	*token;
	char	*varname;
	char	*value;
	int		pos;
	char	*newstr;

	varname = NULL;

	token = list_start(list);
	ret = 0;
	if (ft_strncmp(token->str, "export", 7))
	{
		printf("Something went wrong here, %s is not the export command\n",
			token->str);
		return (1);
	}
	while (token->next && token->next->type == SPACE)
		token = token->next;
	if (!token->next)
	{
		display_env();
		return (0);
	}
	token = token->next;
	if (token->type == WORD && ft_strlen(token->str))
	{
		varname = ft_strdup(token->str);
		value = NULL;
		if (token->next && token->next->type == ASSIGN)
		{
			token = token->next;
			if (token->next)
				value = ft_strdup(token->next->str);
		}
	}
	else if (token->type == STR_DQUOTES || token->type == STR_SQUOTES)
	{
		varname = extract_varname_quoted(token->next->str);
		value = extract_value(token->next->str);
	}
	else
	{
		varname = NULL; // TODO: needs actual error management if the token after 'export' and some spaces is not WORD or STR_...
		display_env();
		return (0);
	}
	pos = var_in_env(varname);
	if (g_envp[pos])
		free(g_envp[pos]);
	newstr = ft_strjoin(varname, "=");
	g_envp[pos] = ft_strjoin(newstr, value);
	if (pos == num_vars_env() - 1)
		g_envp[pos + 1] = ft_strdup("");		// replace string that marks the end of the array
	// if (arraypos != -1)
	// 	; // TODO: update variables
	// else if (token->prev->type = EQUALS)
	// 	;// TODO: add variable names here, if there is an EQUAL sign
	// do nothing if there is no assignment operator
	free(newstr);
	free(varname);
	return (0);
}

// these functions are emtpy dummy functions for now so it compiles
int	exec_unset(t_token **list)
{
	int	ret;

	(void) list;
	ret = 0;
	return (ret);
}

int	exec_env(t_token **list)
{
	t_token	*token;

	token = list_start(list);
	if (ft_strncmp(token->str, "env", 7))
	{
		printf("Something went wrong here, %s is not the cd command\n",
			token->str);
		return (1);
	}
	while (token->next)
	{
		if (token->next->type != SPACE)
		{
			printf("env: %s: No such file or directory\n", token->next->str);
			return (1);
		}
	}
	display_env();
	return (0);
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

