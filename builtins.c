/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 21:59:13 by slakner          ###   ########.fr       */
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

	token = tlist_start(list);
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


//TODO: Update the PWD environment variable here
int	exec_cd(t_token **list)
{
	int		ret;
	int		dir_found;
	t_token	*token;

	token = tlist_start(list);
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
				printf("cd: string not in pwd: %s\n", tlist_start(list)->next->str);
			else
				dir_found = 1;
		}
	}
	ret = chdir(tlist_start(list)->next->str);
	if (ret == -1)
		printf("cd: no such file or directory: %s\n", tlist_start(list)->next->str);
	return (ret);
}

int update_var(char *varname, char *value)
{
	t_dlist	*var;
	
	var = *g_env;
	while (var)
	{
		if (!ft_strncmp(var->content->key, varname, ft_strlen(varname)))
		{
			if(var->content->val)
				free(var->content->val);
			var->content->val = value;
			return (0);
		}
		var = var->next;
	}
	return (1);
}

int	exec_export(t_token **list)
{
	int		ret;
	t_token	*token;
	// char	*varname;
	// char	*value;
	t_dlist	*var;
	//t_kval	*content;

	//varname = NULL;
	token = tlist_start(list);
	ret = 0;
	var = malloc(sizeof(t_dlist));
	var->content = malloc(sizeof(t_kval));
	if (ft_strncmp(token->str, "export", 7))
	{
		printf("Something went wrong here, %s is not the export command\n",
			token->str);
		return (1);
	}
	while (token->next && token->next->type == SPACE)	// skip over spaces
		token = token->next;
	if (!token->next)
	{
		display_env();
		return (0);
	}
	token = token->next;
	if (token->type == WORD && ft_strlen(token->str))
	{
		var->content->key = ft_strdup(token->str);
		if (token->next && token->next->type == ASSIGN) // found the equal sign, next token please
		{
			token = token->next;
			if (token->next && token->next->str)
				var->content->val = ft_strdup(token->next->str);
			else
				var->content->val = ft_strdup("");
		}
	}
	else if (token->type == STR_DQUOTES || token->type == STR_SQUOTES)
	{
		var->content->key = extract_varname_quoted(token->next->str);
		var->content->val = extract_value(token->next->str);
	}
	else
	{
		free(var); // TODO: needs actual error management if the token after 'export' and some spaces is not WORD or STR_...
		display_env();
		return (0);
	}

	if (!var_in_env(var->content->key))
		lstadd_back(g_env, var);
	else
	{
		update_var(var->content->key, var->content->val);
		free(var->content->key);
		free(var->content);
		free(var);
	}
	// 	;// TODO: add variable names here, if there is an EQUAL sign
	// do nothing if there is no assignment operator
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

	token = tlist_start(list);
	if (ft_strncmp(token->str, "env", 7))
	{
		printf("Something went wrong here, %s is not the env command\n",
			token->str);
		return (1);
	}
	while (token->next) // env command does not take arguments
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

	token = tlist_start(list);
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

