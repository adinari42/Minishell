/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 16:10:27 by adinari          ###   ########.fr       */
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
	char	**inpt_split;
	t_parse	parse;
	t_token	**list;
	int		i;

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
			inpt_split = ft_split(inpt, '|');
			free(inpt);
			i = 0;
			while(inpt_split[i])
			{
				list = read_tokens(inpt_split[i]);
				list = merge_quoted_strings(list);
				check_value(*list, envp);
				printf("1--------:\n");
				set_cmd_path(*list, parse);
				printf("printing list :\n");
				print_list(*list);
				// execute_line(*list, parse, envp);
				free_token_list(list);
				sleep(1);
				i++;
			}
		}
		free_2d(&inpt_split);
		// exit(1);
		// system("leaks minishell");
	}
	return (argc);
}