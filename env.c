/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:30:12 by slakner           #+#    #+#             */
/*   Updated: 2022/11/18 22:12:05 by slakner          ###   ########.fr       */
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

int	var_in_env(char *varname)
{
	int		i;
	char	**split;

	i = 0;
	while (g_envp[i] && varname)
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
	int		i;

	i = 0;
	while (g_envp[i])
	{
		printf("%s\n",g_envp[i]);
		i++;
	}
	return ;
}
