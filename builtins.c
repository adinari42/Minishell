/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/11/21 22:53:42 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char	**g_envp;

int	is_builtin(char *str)
{
	size_t	i;
	char	**split;

	i = 0;
	split = ft_split(str, ' ');
	while (split && split[0] && split[0][0]
		&& i < sizeof(g_builtins) / sizeof(const char *const))
	{
		if (!ft_strncmp(split[0], g_builtins[i], ft_strlen(g_builtins[i]) + 1))
		{
			free_split(split);
			return (i + 1);
		}
		i++;
	}
	if (split)
		free_split(split);
	return (0);
}

int	exec_echo(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	int		newline;

	(void) env;
	tkn = list;
	newline = 1;
	if (!builtin_plausible(tkn, "echo"))
		return (1);
	tkn = skip_spaces(tkn);
	if (tkn && !ft_strncmp(tkn->str, "-n", 3))
	{
		newline = 0;
		tkn = skip_spaces(tkn);
	}
	while (tkn)
	{
		write(1, tkn->str, ft_strlen(tkn->str));
		if (tkn->type == SPACE_TKN)
			tkn = skip_spaces(tkn);
		else
			tkn = tkn->next;
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

int	update_var(char *varname, char *value, t_dlist *env)
{
	t_dlist	*var;

	var = env;
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
int	exec_cd(t_token *list, t_dlist *env)
{
	int		ret;
	t_token	*tkn;
	char	pwd[1024];

	ret = 0;
	tkn = tlist_start(list);
	if (!builtin_plausible(tkn, "cd"))
		return (1);
	tkn = skip_spaces(tkn);
	if (tkn && (tkn->type == WORD
			|| tkn->type == STR_DQUOTES || tkn->type == STR_SQUOTES))
		ret = chdir(tkn->str);
	if (ret == -1)
		ret = print_builtin_error("cd", tkn->str);
	getcwd(pwd, 1024);
	update_var("PWD", pwd, env);
	return (ret);
}

int	exec_export(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	t_kval	*cntnt;

	tkn = tlist_start(list);
	cntnt = malloc(sizeof(t_kval));
	if (!builtin_plausible(tkn, "export"))
		return (1);
	tkn = skip_spaces(tkn);
	if (!tkn)
		return (display_env(env));
	if (!valid_identifier(tkn->str))
	{
		free(cntnt);
		return (prnt_err("export", tkn->str, "not a valid identifier"));
	}
	if (tkn->type == WORD && ft_strlen(tkn->str)) //case: varname before 
	{
		cntnt->key = ft_strdup(tkn->str);
		if (tkn->next && tkn->next->type == ASSIGN) // found the equal sign, next tkn please
		{
			tkn = tkn->next;
			if (tkn->next && tkn->next->str)
				cntnt->val = ft_strdup(tkn->next->str);
			else
				cntnt->val = ft_strdup("");
		}
		else
		{
			free(cntnt->key);
			free(cntnt);
			return (0);
		}
	}
	else if (tkn->type == STR_DQUOTES || tkn->type == STR_SQUOTES)
	{
		cntnt->key = extract_varname_quoted(tkn->next->str);
		cntnt->val = extract_value(tkn->next->str);
	}
	else
	{
		free(cntnt); // TODO: needs actual error management if the tkn after 'export' and some spaces is not WORD or STR_...
		display_env(env);
		return (0);
	}
	if (!var_in_env(cntnt->key, env))
		lstadd_back(&env, lstnew(cntnt));
	else
	{
		update_var(cntnt->key, cntnt->val, env);
		free_kval(cntnt);
	}
	return (0);
}

// unset without an argument returns 0
int	exec_unset(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	t_dlist	*var;

	tkn = tlist_start(list);
	var = env;
	if (!builtin_plausible(tkn, "unset"))
		return (1);
	tkn = skip_spaces(tkn);
	while (var)
	{
		if (!ft_strncmp(var->content->key, tkn->str, ft_strlen(tkn->str)))
		{
			if (!tkn->next || tkn->next->type == SPACE_TKN)
			{
				lstdel_elem(&env, var);
				return (0);
			}
		}
		var = var->next;
	}
	return (0);
}

int	exec_env(t_token *list, t_dlist *env)
{
	t_token	*tkn;

	tkn = tlist_start(list);
	if (!builtin_plausible(tkn, "env"))
		return (1);
	tkn = skip_spaces(tkn);
	if (tkn) // env command does not take arguments
	{
		printf("env: %s: No such file or directory\n", tkn->next->str);
		return (1);
	}
	display_env(env);
	return (0);
}

void	exec_exit(t_token *list, t_dlist **env, t_pipe *data)
{
	t_token	*tkn;
	char	*tokenstr;

	tkn = list;
	if (!builtin_plausible(tkn, "exit"))
		return ;
	tkn = skip_spaces(tkn);
	if (tkn && tkn->next)
	{
		tokenstr = tkn->str;
		while (*(tokenstr))
		{
			if (!ft_isdigit(*tokenstr))
			{
				printf("minishell: exit: %s: numeric argument required\n", tkn->str);
				exit_with_value(255, env);
			}
			tokenstr ++;
		}
		data->error_code = ft_atoi(tkn->str);
		tkn = skip_spaces(tkn);
		if (tkn && tkn->type != SPACE_TKN)
		{
			printf("minishell: exit: too many arguments\n");
			data->error_code = 1;
			return ;
		}
	}
	exit_with_value(data->error_code, env);
}

int	exec_pwd(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	char	pwd[1024];

	(void) env;
	tkn = tlist_start(list);
	if (!builtin_plausible(tkn, "pwd"))
		return (1);
	tkn = skip_spaces(tkn);
	if (tkn)
	{
		printf("pwd: too many arguments");
		return (1);
	}
	getcwd(pwd, 1024);
	printf("%s \n", pwd);
	return (0);
}

int	builtin_plausible(t_token *tkn, char *builtin)
{
	if (ft_strncmp(tkn->str, builtin, ft_strlen(builtin) + 1))
	{
		printf("Something went wrong here, %s is not the %s command.\n",
			tkn->str, builtin);
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

// varnames can contain letters, digits and underscores
// a varname can't start with a digit
int	valid_identifier(char *varname)
{
	if (ft_isdigit(*varname))
		return (0);
	while (*varname)
	{
		if (!ft_isalpha(*varname) && !ft_isdigit(*varname)
			&& *varname != '_')
			return (0);
		varname ++;
	}
	return (1);
}

int	prnt_err(char *cmd, char *arg, char *errstr)
{
	printf("minishell: %s: `%s': %s\n", cmd, arg, errstr);
	return (1);
}
