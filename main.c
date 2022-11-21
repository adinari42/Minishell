/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/21 12:02:53 by adinari          ###   ########.fr       */
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
	t_token	**list;

	if (argc != 1)
		return (1);
	init_signals();
	parse.split_envp = envp_parse(envp);
	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env
	// display_splitenvp(parse, argv);
	while (1)
	{
		inpt = readline("Minishell$ ");
		if (inpt && inpt[0])
		{
			add_history(inpt);
			printf("%s\n", inpt);
			list = read_tokens(inpt);
			list = merge_quoted_strings(list);
			// printf("After quotes treatment: \n");
			// print_list(*list);
			// printf("After removing spaces: \n");
			check_value(*list, envp);
			printf("printing list :\n");
			print_list(*list);
			printf("here\n");
			const char arg[] = "-l main.c";
			execve("/usr/bin/wc",  (char * const *) arg, (char * const *) *envp);
			free(inpt);
			free_token_list(list);
		}
		// system("leaks minishell");
	}
	return (argc);
}
