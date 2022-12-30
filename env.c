/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:30:12 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:16:01 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**envp_parse(char **envp)
{
	int		j;
	char	**envp_parse;

	j = -1;
	while (envp[++j])
	{
		printf("%s\n", envp[j]);
		if (!ft_strncmp(envp[j], "PATH=", 5))
			break ;
	}
	envp_parse = ft_split(*(envp + j) + 5, ':');
	return (envp_parse);
}

char	*get_value_from_key(t_dlist *var, char *varname, int count, t_pipe *dt)
{
	char	*value;
	char	*str;

	str = ft_substr(varname, 0, count);
	value = NULL;
	if (!ft_strncmp("?", str, ft_strlen(str)))
		value = ft_strjoin_free_str1(ft_itoa(dt->error_code),
				varname + (count + 1));
	else
	{
		while (var)
		{
			if (!ft_strncmp(var->content->key, str, ft_strlen(str) + 1))
			{
				value = ft_strdup(var->content->val);
				break ;
			}
			var = var->next;
		}
		if (!value)
			value = ft_strdup("");
		value = ft_strjoin_free_str1(value, varname + count);
	}
	free(str);
	return (value);
}

char	*expand_var_in_str(t_dlist *var, char *varname, t_pipe *data)
{
	char	*value;
	int		count;

	count = 0;
	while (varname[count]
		&& (ft_isalnum(varname[count]) || varname[count] == '_'))
		count++;
	value = get_value_from_key(var, varname, count, data);
	return (value);
}

//assumption here: quotes have been stripped already
char	*extract_varname_quoted(char *tokenstr)
{
	char	*varname;
	char	*ptr;
	char	**split;

	ptr = ft_strchr(tokenstr, '=');
	if (!ptr)
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
	return (varname);
}

char	*extract_value(char *tokenstr)
{
	char	*varname;
	char	*ptr;
	char	**split;

	ptr = ft_strchr(tokenstr, '=');
	if (!ptr)
		return (NULL);
	else
	{
		split = ft_split(tokenstr, '=');
		varname = ft_strdup(split[1]);
		free_split(split);
	}
	return (varname);
}

