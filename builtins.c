/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/25 15:22:50 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	size_t	i;

	i = 0;
	while (i < sizeof(g_builtins) / sizeof(const char *const))
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
	int		newline;

	token = tlist_start(list);
	newline = 1;
	if (!builtin_plausible(token, "echo"))
		return (1);
	token = skip_spaces(token);
	if (token && !ft_strncmp(token->str, "-n", 3))
	{
		newline = 0;
		token = skip_spaces(token);
	}
	while (token)
	{
		write(1, token->str, ft_strlen(token->str));
		token = token->next;
	}
	if (newline)
		printf("\n");
	return (0);
}

int	update_var(char *varname, char *value)
{
	t_dlist	*var;

	var = *g_env;
	while (var)
	{
		if (!ft_strncmp(var->content->key, varname, ft_strlen(varname)))
		{
			if (var->content->val)
				free(var->content->val);
			var->content->val = ft_strdup(value);
			return (0);
		}
		var = var->next;
	}
	return (1);
}


// if cd has more than one argument, bash ignores anything after the first and just changes dir anyway
// -> we don't have to do any special handling of too many arguments
int	exec_cd(t_token **list)
{
	int		ret;
	t_token	*token;
	char	pwd[1024];

	token = tlist_start(list);
	if (!builtin_plausible(token, "cd"))
		return (1);
	token = skip_spaces(token);
	if (token->type == WORD 
		|| token->type == STR_DQUOTES || token->type == STR_SQUOTES)
		ret = chdir(token->str);
	if (ret == -1)
		ret = print_builtin_error("cd", token->str);
	getcwd(pwd, 1024);
	update_var("PWD", pwd);
	return (ret);
}

int	exec_export(t_token **list)
{
	t_token	*token;
	t_kval	*content;

	token = tlist_start(list);
	content = malloc(sizeof(t_kval));
	if (!builtin_plausible(token, "export"))
		return (1);
	token = skip_spaces(token);
	if (!token)
		return (display_env());
	if (token->type == WORD && ft_strlen(token->str))
	{
		content->key = ft_strdup(token->str);
		if (token->next && token->next->type == ASSIGN) // found the equal sign, next token please
		{
			token = token->next;
			if (token->next && token->next->str)
				content->val = ft_strdup(token->next->str);
			else
				content->val = ft_strdup("");
		}
		else
		{
			free(content->key);
			free(content);
			return (0);
		}
	}
	else if (token->type == STR_DQUOTES || token->type == STR_SQUOTES)
	{
		content->key = extract_varname_quoted(token->next->str);
		content->val = extract_value(token->next->str);
	}
	else
	{
		free_kval(content); // TODO: needs actual error management if the token after 'export' and some spaces is not WORD or STR_...
		display_env();
		return (0);
	}

	if (!var_in_env(content->key))
		lstadd_back(g_env, lstnew(content));
	else
	{
		update_var(content->key, content->val);
		free_kval(content);
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
	if (!builtin_plausible(token, "env"))
		return (1);
	token = skip_spaces(token);
	if (token) // env command does not take arguments
	{
		printf("env: %s: No such file or directory\n", token->next->str);
		return (1);
	}
	display_env();
	return (0);
}

int	exec_exit(t_token **list)
{
	t_token	*token;
	char	*tokenstr;
	int		ret;

	token = tlist_start(list);
	ret = 0;
	if (!builtin_plausible(token, "exit"))
		return (1);
	token = skip_spaces(token);
	if (token && token->next)
	{
		token = skip_spaces(token);
		if (token)
		{
			printf("minishell: exit: too many arguments\n");
			return (1);
		}
	}
	else if (token)
	{
		tokenstr = token->str;
		while (*tokenstr)
		{
			if (!ft_isdigit(*tokenstr))
			{
				printf("minishell: exit: %s: numeric argument required\n",
					token->str);
			}
			tokenstr ++;
		}
		ret = ft_atoi(token->str);
	}
	exit_with_value(ret);
	return (0);
}

int	exec_pwd(t_token **list)
{
	t_token	*token;
	char	pwd[1024];

	token = tlist_start(list);
	if (!builtin_plausible(token, "pwd"))
		return (1);
	token = skip_spaces(token);
	while (token->next)
	{
		token = token->next;
		if (token->type != SPACE)
		{
			printf("pwd: too many arguments");
			return (1);
		}
	}
	getcwd(pwd, 1024);
	printf("%s \n", pwd);
	return (0);
}

int	builtin_plausible(t_token *token, char *builtin)
{
	if (ft_strncmp(token->str, builtin, ft_strlen(builtin) + 1))
	{
		printf("Something went wrong here, %s is not the %s command.\n",
			token->str, builtin);
		return (0);
	}
	return (1);
}

int	print_builtin_error(char *builtin, char *dir)
{
	if (ft_strncmp(builtin, "cd", 3))
		access(dir, X_OK);
	if (errno == EACCES)
		printf("minishell: %s: %s/: permission denied\n", builtin, dir);
	else if (errno == ENOTDIR)
		printf("minishell: %s: %s: Not a directory\n", builtin, dir);
	else if (errno == ENAMETOOLONG)
		printf("minishell: %s: %s: File name too long\n", builtin, dir);
	else if (errno == ENOENT)
		printf("minishell: %s: %s: No such file or directory\n", builtin, dir);
	return (1);
}