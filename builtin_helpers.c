/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:25:25 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 21:17:11 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	is_builtin(char *str)
{
	size_t						i;
	char						**split;
	static const char *const	builtins[] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	split = ft_split(str, ' ');
	while (split && split[0] && split[0][0]
		&& i < sizeof(builtins) / sizeof(const char *const))
	{
		if (!ft_strncmp(split[0], builtins[i], ft_strlen(builtins[i]) + 1))
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

void	write_export_var(t_kval *cntnt, t_dlist *env)
{
	if (!var_in_env(cntnt->key, env))
		lstadd_back(&env, lstnew(cntnt));
	else
	{
		update_var(cntnt->key, cntnt->val, env);
		free_kval(cntnt);
	}
}

t_kval	*extract_keyvalue_unquoted(t_token *tkn)
{
	t_kval	*cntnt;

	cntnt = malloc(sizeof(t_kval *));
	cntnt->key = ft_strdup(tkn->str);
	if (tkn->next && tkn->next->type == ASSIGN)
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
	}
	return (cntnt);
}
