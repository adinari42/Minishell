/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:30:12 by slakner           #+#    #+#             */
/*   Updated: 2022/12/23 04:24:57 by adinari          ###   ########.fr       */
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
	int	count;

	//iterate through varname, count the length from beginning to first s_quote******
	count = 0;
	while (varname[count] && varname[count] != '\'')
		count++;
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
			if (!ft_strncmp(var->content->key, str, ft_strlen(str)))
			{
				value = ft_strdup(var->content->val);
				break ;
			}
			var = var->next;
		}
	}
	free(str);
	if (varname[count] == '\'')
		value = ft_strjoin_free_str1(value, "'");
	//join the rest of the string to the end of it***/
	count++;
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
	printf("varname from extract_varname_quoted: %s\n", varname);
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
	return (lstsize(env));
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
	while (var && var->content)
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

	if (!env || !*env)
		return (NULL);
	i = 0;
	elem = *env;
	env_c = malloc(sizeof(char *) * (lstsize(*env) + 1));
	if (!env_c)
		return (NULL);
	while (i < lstsize(*env))
	{
		if (elem->content && elem->content->key)
		{
			buf = ft_strjoin(elem->content->key, "=");
			if (elem->content->val && (elem->content->val)[0])
				env_c[i] = ft_strjoin(buf, elem->content->val);
			else
				env_c[i] = ft_strdup(buf);
			free(buf);
		}
		else
			env_c[i] = ft_strdup("");
		i++;
		elem = elem->next;
	}
	*(env_c + i) = NULL;
	return (env_c);
}
