/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/18 15:26:29 by slakner          ###   ########.fr       */
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

void	display_list(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while(tmp)
	{
		printf(">%s\n", tmp->str);
		tmp = tmp->next;
	}
}

void	free_ll(t_token *stack)
{
	t_token	*tmp1;
	t_token 	*tmp;

	tmp = stack;
	tmp1 = NULL;
	while (tmp)
	{
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
	stack = NULL;
}

void	free_2d(char ***to_free)
{
	size_t	i;

	i = 0;
	if (*to_free == NULL)
		return ;
	while ((*to_free)[i] != NULL)
	{
		free((*to_free)[i]);
		++i;
	}
	free(*to_free);
	*to_free = NULL;
}
int	push(t_token **thestack, char *thevalue)
{
	t_token	*newnode;
	t_token	*temp;

	temp = NULL;
	newnode = malloc(sizeof(t_token));
	if (newnode == NULL)
	{
		write(2, "Error\n", 6);
		free(newnode);
		return (0);
	}
	newnode->str = thevalue;
	newnode->next = NULL;
	if (*thestack == NULL)
		*thestack = newnode;
	else
	{
		temp = *thestack;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (1);
}

void	quote_tokens(t_token *tokens, char* line) {

    // const char *line = "'foobar'|cat'mousebar'sum";
    char	delim[2] = "\'\"";
    char	*p;
	char 	*first;
	char 	*second;
	char	*str;
	// char	c;
	int	j = 0;
	size_t len;
	int i = 0;
		p = line;
	
		first = NULL;
		second = NULL;
		len = -1;
		while (p && *p) /* for each char in line */
		{   i = 0;
			while (delim[i] && !first)
			{
				if (*p == delim[i])
					j = i;
				i++;
			}
			if (!first && *p == delim[j])             /* find 1st delim */
			{
				first = p;
				first++;                   /* set start ptr  */
			}	
			else if (!second && *p == delim[j])        /* find 2nd delim */
			{
				str = ft_substr(first, 0, len);   
				len = -1;                    /* set end ptr    */
				second = p;
			}
			if (first && second) {                     /* if both set    */
				push(&tokens, str);
				first = NULL;
				second = NULL;
			}
			if (first)
				len++;
			p++;
		}
	}



int main(int argc, char **argv, char **envp)
{
	char		*inpt;
	t_parse		parse;
	t_token		**list;

	
	parse.split_envp = envp_parse(envp);
	display_splitenvp(parse, argv);
	while (1)
	{
		list = malloc(sizeof(t_token));
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
			// exec("/bin/cat", args, envp);

			exec(NULL, NULL, envp);
			handle_commandstr(list);
			free_token_list(list);
		}
		if (inpt)
			free(inpt);
		//system("leaks minishell");
	}
	system("leaks minishell");
	
	return (argc);
}
