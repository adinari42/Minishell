/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/13 23:35:39 by slakner          ###   ########.fr       */
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

void	display_splitenvp(t_parse parse, char **argv)
{
	int	i;

	i = 0;
	printf("%s envp parse: ", argv[0]);
	while (parse.split_envp[i])
		printf("%s\n", parse.split_envp[i++]);
}

int	main(int argc, char **argv, char **envp)
{
	char	*inpt;
	t_parse	parse;

	if (argc != 1)
		return (1);
	init_signals();
	parse.split_envp = envp_parse(envp);
	display_splitenvp(parse, argv);
	while (1)
	{
		inpt = readline("Minishell$ ");
		if (inpt && inpt[0])
		{
			add_history(inpt);
			printf("%s\n", inpt);
			read_tokens(inpt);
			// do sometihng with tokens here;
			// then:
			// free_token_list();
		}
	}
	return (argc);
}
