/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/12/29 23:51:56 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (tkn && !ft_strncmp(tkn->str, "-n", 3))
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
		write(1, "\n", 1);
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
	if (tkn)
	{
		printf("exit\n");
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
