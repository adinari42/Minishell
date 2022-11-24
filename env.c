/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:30:12 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 21:40:48 by slakner          ###   ########.fr       */
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

char	*get_value_from_key(t_dlist *var, char *varname, t_pipe *data)
{
	char	*value;
	char	*str;
	int		count;

	//iterate through varname, count the length from beginning to first s_quote******
	count = 0;
	while (varname[count] && (ft_isalnum(varname[count]) || varname[count] == '_'))
		count++;
	//printf("varname %s, count %d\n", varname, count);
	//extract that first string*****/
	str = ft_substr(varname, 0, count);
	//check and replace with env value***/
	value = NULL;
	if (!ft_strncmp("?", str, ft_strlen(str)))
		value = ft_itoa(data->error_code);
	else
	{
		while (var)
		{
			if (!ft_strncmp(var->content->key, str, ft_strlen(str) + 1))		// +1 so we also compare the terminating null byte
			{
				value = ft_strdup(var->content->val);
				break ;
			}
			var = var->next;
		}
		if (!value)
			value = ft_strdup("");					// this needs to be malloced instead of null so we can properly free when this is used by the builtins
	}
	free(str);
	value = ft_strjoin_free_str1(value, varname + count);
	return (value);
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
	//printf("varname from extract_varname_quoted: %s\n", varname);
	return (varname);
}

char	*extract_value(char *tokenstr)
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

int	num_vars_env(t_dlist *env)
{
	return (lstsize(*g_env));
}

int	var_in_env(char *varname, t_dlist *env)
{
	t_dlist	*elem;

	elem = env;
	while (elem)
	{
		if (!ft_strncmp(varname, elem->content->key, ft_strlen(varname) + 1))
			return (1);
		elem = elem->next;
	}
	return (0);
}

int	display_env(t_dlist *env)
{
	t_dlist	*var;

	var = env;
	while (var && var->content
		&& ft_strncmp(var->content->key, "?", 2))
	{
		printf("%s=", var->content->key);
		if (var->content->val)
			printf("%s", var->content->val);
		printf("\n");
		var = var->next;
	}
	return (0);
}

char	**env_list_to_char_arr(t_dlist **env)
{
	int		i;
	t_dlist	*elem;
	char	**env_c;
	char	*buf;

	env_c = malloc(sizeof(char *) * (lstsize(*env) + 1));
	//printf("lstsize: %d\n", lstsize(*env));
	i = 0;
	if (!env && !env_c)
		return (NULL);
	elem = env[0];
	while (i < lstsize(*env))
	{
		buf = ft_strjoin(elem->content->key, "=");
		if (elem->content->val && *(elem->content->val))
		{
			env_c[i] = ft_strjoin(buf, elem->content->val);
			free(buf);
		}
		else
			env_c[i] = buf;
		i++;
		elem = elem->next;
	}
	*(env_c + i) = NULL;
	return (env_c);
}
