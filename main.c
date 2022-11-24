/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 14:52:53 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	**envp_parse(char **envp)
// {
// 	int		j;
// 	char	**envp_parse;

// 	j = -1;
// 	while (envp[++j])
// 	{
// 		if (!ft_strncmp(envp[j], "PATH=", 5))
// 			break ;
// 	}
// 	envp_parse = ft_split(*(envp + j) + 5, ':');
// 	return (envp_parse);
// }

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
	//t_parse	parse;
	t_token	**list;
	char	**envp_c;

	if (argc != 1)
		return (1);
	init_signals();
	init_env_llist(envp);
	//parse.split_envp = envp_parse(envp);
	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env 
	//g_envp = envp;
	//display_splitenvp(parse, argv);
	while (1)
	{
		inpt = readline("Minishell$ ");
		if (inpt && inpt[0])
		{
			add_history(inpt);
			printf("%s\n", inpt);
			list = read_tokens(inpt);
			list = merge_quoted_strings(list);
			printf("After quotes treatment: \n");
			print_list(*list);
			printf("After removing spaces: \n");
			list = remove_spaces(list);
			print_list(*list);
			
			// char *args[2];
			// args[0] = "/bin/cat";
			// args[1] = "ps";
			//exec("/bin/cat", args, envp);

			//exec(NULL, NULL, envp);
			
			//system("leaks minishell");
			// printf("After quotes treatment: \n");
			// print_list(*list);
			// printf("After removing spaces: \n");
			envp_c = env_list_to_char_arr(g_env);
			for (int i = 0; envp[i] && ft_strncmp(envp[i], "", 1); i++)
				printf("envp: %s\n", envp[i]);
			//check_value(*list, envp_c);
			free(envp_c);
			// we need a function here that deletes empty nodes
			//list = remove_empty(list);
			printf("After check_value, printing list:\n");
			print_list(*list);
			handle_commandstr(list);
			if (inpt)
				free(inpt);
			// free_token_list(list);
		 	//free(parse.split_envp);
		}
		//system("leaks minishell");
	}
	return (argc);
}
