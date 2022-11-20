/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 22:30:12 by slakner           #+#    #+#             */
/*   Updated: 2022/11/20 22:00:31 by slakner          ###   ########.fr       */
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

// int	num_vars_env()
// {
// 	int	i;

// 	i = 0;
// 	//while (ft_strncmp(g_envp[i], "", 1))
// 	while (g_envp[i])
// 		i++;
// 	return (i);
// }

int	num_vars_env()
{
	return lstsize(*g_env);
}

// int	var_in_env(char *varname)
// {
// 	int		i;
// 	char	**split;

// 	i = 0;
// 	while (g_envp[i] && varname)
// 	{
// 		split = ft_split(g_envp[i], '=');
// 		if (split && *split && !ft_strncmp(split[0], varname, ft_strlen(split[0]) + 1))
// 		{
// 			free_split(split);
// 			return (i);
// 		}
// 		free_split(split);
// 		i++;
// 	}
// 	return (i);
// }

int	var_in_env(char *varname)
{
	t_dlist *elem;

	elem = *g_env;
	while (elem)
	{
		if (!ft_strncmp(varname, elem->content->key, ft_strlen(varname) + 1))
			return (1);
		elem = elem->next;
	}
	return (0);
}

// void	display_env(void)
// {
// 	int		i;

// 	i = 0;
// 	while (g_envp[i])
// 	{
// 		printf("%s\n",g_envp[i]);
// 		i++;
// 	}
// 	return ;
// }

void	display_env(void)
{
	t_dlist	*var;

	var = *g_env;
	while (var && var->content)
	{
		printf("%s=", var->content->key);
		if (var->content->val && *(var->content->val))
			printf("%s", var->content->val);
		printf("\n");
		var = var->next;
	}
}

char	**env_list_to_char_arr(t_dlist **env)
{
	int		i;
	t_dlist	*elem;
	char	**env_c;
	char	*buf;

	env_c = malloc(sizeof(char *) * lstsize(*env));
	i = 0;
	if (!env)
		return (NULL);
	elem = *env;
	while (i < lstsize(*env))
	{
		buf = ft_strjoin(elem->content->key, "=");
		env_c[i] = ft_strjoin(buf, elem->content->val);
		free(buf);
		i++;
	}
	env_c[i] = ft_strdup("");
	return (env_c);
}