/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expandvar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 21:21:13 by adinari           #+#    #+#             */
/*   Updated: 2022/11/16 22:02:43 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*value_expand(char **envp, char *var)
{
	int		j;
	char	*value;
	int		len;

	len = ft_strlen(var);
	j = -1;
	while (envp[++j])
	{
		if (!ft_strncmp(envp[j], var, len))
		{
			len += 1;
			break ;
		}
	}
	if (len != ft_strlen(var))
	{
		value = *(envp + j) + len;
		return (value);
	}
	return (ft_strdup(" "));
}


int main(int argc, char **argv, char **envp)//(int argc, char **argv, char **envp)
{
	char *value;

	if (*argv[1] == '$')
	{	value = value_expand(envp, argv[1] + 1);
		printf("%s\n", value);
	}
	printf("%d\n", argc);
}