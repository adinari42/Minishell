/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/18 19:56:32 by slakner          ###   ########.fr       */
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


//TODO: Update the PWD environment variable here
int	exec_cd(t_token **list)
{
	int		ret;
	int		dir_found;
	t_token	*token;

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
	//printf("%d \n", ret);
	return (ret);
}

char	**envp_parse(char **envp)
{
	int		j;
	char	**envp_parse;

	j = 0;
	while (envp[j])
	{
		printf("envp[i]: %s\n", envp[j]);
		j++;
	}
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], "PATH=", 5))
			break ;
	}
	envp_parse = ft_split(*(envp + j) + 5, ':');
	return (envp_parse);
}


//assumption here: quotes have been stripped already
char	*extract_varname_quoted(char *tokenstr)
{
	char	*varname;
	char	*ptr;
	char	**split;

	ptr = ft_strchr(tokenstr, '=');
	if (!ptr)	// case: no equal sign found in string, probably needs actual error management to behave like bash
		return (NULL);
	else
	{
		split = ft_split(tokenstr, '=');
		varname = ft_strdup(split[0]);
		free_split(split);
	}
	if (ft_strchr(varname, ' '))
	{
		printf("export: not valid in this context: %s\n", varname);
		free(varname);
	}
	printf("varname from extract_varname_quoted: %s\n", varname);
	return (varname);
}

char *extract_value(char *tokenstr)
{
	char	*varname;
	char	*ptr;
	char	**split;

	ptr = ft_strchr(tokenstr, '=');
	if (!ptr)	// case: no equal sign found in string, probably needs actual error management to behave like bash
		return (NULL);
	else
	{
		split = ft_split(tokenstr, '=');
		varname = ft_strdup(split[1]);
		free_split(split);
	}
	printf("varname from extract_varname_quoted: %s\n", varname);
	return (varname);
}

int	var_in_env(char *varname)
{
	int		i;
	char	**split;

	i = 0;
	while (g_envp[i])
	{
		split = ft_split(g_envp[i], '=');
		if (!ft_strncmp(split[0], varname, ft_strlen(split[0]) + 1))
		{
			free_split(split);
			return (i);
		}
		free_split(split);
		i++;
	}
	return (-1);
}

void	display_env(void)
{
	return ;
}

// these functions are emtpy dummy functions for now so it compiles
int	exec_export(t_token **list)
{
	int		ret;
	t_token	*token;
	char	*varname;
	char	*value;
	int		arraypos;
	
	token = list_start(list);
	ret = 0;
	if (ft_strncmp(token->str, "export", 7))
	{
		printf("Something went wrong here, %s is not the cd command\n",
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
	if (token->type == WORD)
	{
		varname = ft_strdup(token->next->str);
		value = NULL;
		if (token->next && token->next->type == EQUAL)
		{
			token = token->next;
			if (token->next)
				value = ft_strdup(token->next->str);
		}
	}
	else if (token->next->type == STR_DQUOTES || token->next->type == STR_SQUOTES)
	{
		varname = extract_varname_quoted(token->next->str);
		value = extract_value(token->next->str);
	}
	else
		varname = NULL; // TODO: needs actual error management if the token after 'export' and some spaces is not WORD or STR_...
	arraypos = var_in_env(varname);
	// if (arraypos != -1)
	// 	; // TODO: update variables
	// else
	// 	;// TODO: handle nonexistent variable names here
	ret = 0;
	free(varname);
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

