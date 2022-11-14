/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/14 18:31:20 by adinari          ###   ########.fr       */
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

void	display_list(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = tokens;
	while(tmp)
	{
		printf(">%s\n", tmp->token);
		tmp = tmp->next;
	}
}

void	free_ll(t_tokens *stack)
{
	t_tokens	*tmp1;
	t_tokens 	*tmp;

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
int	push(t_tokens **thestack, char *thevalue)
{
	t_tokens	*newnode;
	t_tokens	*temp;

	temp = NULL;
	newnode = malloc(sizeof(t_tokens));
	if (newnode == NULL)
	{
		write(2, "Error\n", 6);
		free(newnode);
		return (0);
	}
	newnode->token = thevalue;
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
// void	tokenizer1(t_tokens *a, char *line) 
// {
//     // const char *line = "'foobar'|cat'mousebar'sum";
//     char delim = '\'';
//     char *p = (char *)line, *sp = NULL, *ep = NULL;
// 	int first;
// 	int	second;
// 	first = 0;
// 	second = 0;
//     size_t i = 0;

//    for (; *p; p++) {                /* for each char in line */
//         if (!sp && *p == delim)             /* find 1st delim */
//             sp = p, sp++;                   /* set start ptr  */
//         else if (!ep && *p == delim)        /* find 2nd delim */
//             ep = p;                         /* set end ptr    */
//         if (sp && ep) {                     /* if both set    */
//             char substr[ep - sp + 1];       /* declare substr */
//             for (i = 0, p = sp; p < ep; p++)/* copy to substr */
//                 substr[i++] = *p;
//             substr[ep - sp] = 0;            /* nul-terminate  */

//             // printf ("single-quoted string : %s\n", substr);
//             sp = ep = NULL;
// 			// push(&a, ft_substr(substr, first, );
//         }
//     }
// }
void	find_token(t_tokens *tokens, char* line) {

    // const char *line = "'foobar'|cat'mousebar'sum";
    char delim = '\'';
    char *p = (char *)line;
	char *first = NULL;
	char *second = NULL;
	char *str;
	size_t len = -1;

    while (p && *p) {                /* for each char in line */
        if (!first && *p == delim)             /* find 1st delim */
            first = p, first++;                   /* set start ptr  */
        else if (!second && *p == delim)        /* find 2nd delim */
        {
			str = ft_substr(first, 0, len);   
			len = -1;                    /* set end ptr    */
			second = p;
		}
		if (first && second) {                     /* if both set    */
            // printf ("single-quoted string : %s\n", str);
			push(&tokens, str);
            first = second = NULL;
			
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
	t_tokens	*tokens;
	t_tokens	*tmp;

	tokens = malloc(sizeof(t_tokens));
	parse.split_envp = envp_parse(envp);
	display_splitenvp(parse, argv);
	while (1)
	{
		inpt = readline("Minishell$ ");
		if(inpt && inpt[0])
			add_history(inpt);
		find_token(tokens, inpt);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
		display_list(tokens);
		free_ll(tokens);
	}
	return (argc);
}
