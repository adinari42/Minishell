/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:33:06 by adinari           #+#    #+#             */
/*   Updated: 2022/11/18 21:40:47 by slakner          ###   ########.fr       */
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
	while (tmp)
	{
		printf(">%s\n", tmp->token);
		tmp = tmp->next;
	}
}

void	free_ll(t_tokens *stack)
{
	t_tokens	*tmp1;
	t_tokens	*tmp;

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

/*returns last node of the ll*/
t_tokens	*ft_lasttoken(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	quote_tokens(t_token *tokens, char* line) 
{
    // const char *line = "'foobar'|cat'mousebar'sum";
    char	delim[2] = "\'\"";
    char	*p;
	char 	*first;
	char 	*second;
	char	*str;
	int	j = 0;
	size_t len;
	int i;
	t_token *tmp;

	p = line;
	first = NULL;
	second = NULL;
	len = -1;
	while (p && *p) /* for each char in line */
	{   
		i = 0;
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
			// free(str);
		}
		if (first)
			len++;
		p++;
	}
	tmp = ft_lasttoken(tokens);
	tmp->next = NULL;
}



int main(int argc, char **argv, char **envp)
{
	char		*inpt;
	t_parse		parse;
	t_token	*tokens;
	t_token	*tmp;

	parse.split_envp = envp_parse(envp);
	display_splitenvp(parse, argv);
	while (1)
	{
		tokens = malloc(sizeof(t_token));
		inpt = readline("Minishell$ ");
		if(inpt && inpt[0])
			add_history(inpt);
		quote_tokens(tokens, inpt);
		tmp = tokens;
		tokens = tokens->next;
		free(tmp);
		display_list(tokens);
		free_ll(tokens);
		free(inpt);
		// system("leaks minishell");
	}
	return (argc);
}
