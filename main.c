/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:26:14 by adinari           #+#    #+#             */
/*   Updated: 2022/11/24 18:12:59 by slakner          ###   ########.fr       */
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
	char	**inpt_split;
	t_parse	parse;
	t_token	**list;
	int		i;

	if (argc != 1)
		return (1);
	init_signals();
	//(void) envp;
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

// int	main(int argc, char **argv, char **envp)
// {
// 	char	*inpt;
// 	//t_parse	parse;
// 	t_token	**list;
// 	char	**envp_c;

// 	if (argc != 1)
// 		return (1);
// 	init_signals();
// 	//(void) envp;
// 	init_env_llist(envp);
// 	//parse.split_envp = envp_parse(envp);
// 	printf("%c", argv[0][0]);//to silence unused argv error and not use dislay env 
// 	//g_envp = envp;
// 	//display_splitenvp(parse, argv);
// 	while (1)
// 	{
// 		inpt = readline("Minishell$ ");
// 		if (inpt && inpt[0])
// 		{
// 			add_history(inpt);
// 			printf("%s\n", inpt);
// 			list = read_tokens(inpt);
// 			list = merge_quoted_strings(list);
// 			printf("After quotes treatment: \n");
// 			print_list(*list);
// 			// printf("After removing spaces: \n");
// 			// list = remove_spaces(list);
// 			// print_list(*list);

// 			// char *args[2];
// 			// args[0] = "/bin/cat";
// 			// args[1] = "ps";
// 			//exec("/bin/cat", args, envp);

// 			//exec(NULL, NULL, envp);
		
					
// 			envp_c = env_list_to_char_arr(g_env);
// 			for (int i = 0; envp[i] && ft_strncmp(envp[i], "", 1); i++)
// 				printf("envp: %s\n", envp[i]);
// 			// //check_value(*list, envp_c);
// 			free_char_arr(envp_c);

			
// 			// we need a function here that deletes empty nodes
// 			//list = remove_empty(list);
// 			// printf("After check_value, printing list:\n");
// 			// print_list(*list);
// 			// handle_commandstr(list);
// 			free_token_list(list);
// 			// if (list)
// 			// 	free(list);
// 		 	//free(parse.split_envp);
// 		}
// 		if (inpt)
// 			free(inpt);
// 		//system("leaks minishell");
// 	}
// 	return (argc);
// }
