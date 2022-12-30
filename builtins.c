/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 20:03:18 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:01:31 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_echo(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	int		newline;

	(void) env;
	tkn = list;
	newline = 1;
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

// if cd has more than one argument,
// bash ignores anything after the first and just changes dir anyway
// -> we don't have to do any special handling of too many arguments
int	exec_cd(t_token *list, t_dlist *env, t_pipe *data)
{
	int		ret;
	t_token	*tkn;
	char	pwd[1024];
	char	*homedir;

	ret = 0;
	tkn = list;
	homedir = NULL;
	tkn = skip_spaces(tkn);
	if (!tkn)
	{
		homedir = expand_var_in_str(env, "HOME", data);
		chdir(homedir);
		free(homedir);
	}
	else if (tkn && (tkn->type == WORD
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

	tkn = list;
	tkn = skip_spaces(tkn);
	tkn = skip_empty(tkn);
	cntnt = NULL;
	if (!tkn)
		return (display_env(env));
	if (!valid_identifier(tkn->str))
		return (prnt_err("export", tkn->str, "not a valid identifier"));
	if (tkn->type == WORD && ft_strlen(tkn->str))
		cntnt = extract_keyvalue_unquoted(tkn);
	else if (tkn->type == STR_DQUOTES || tkn->type == STR_SQUOTES)
	{
		cntnt = malloc(sizeof(t_kval));
		cntnt->key = extract_varname_quoted(tkn->next->str);
		cntnt->val = extract_value(tkn->next->str);
	}
	else
		return (display_env(env));
	write_export_var(cntnt, env);
	return (0);
}

// unset without an argument returns 0
int	exec_unset(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	t_dlist	*var;

	tkn = list;
	var = env;
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
