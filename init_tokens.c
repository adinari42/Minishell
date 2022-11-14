/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 22:04:22 by adinari           #+#    #+#             */
/*   Updated: 2022/11/14 13:49:38 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	push(t_tokens **thestack, char *tokens_split)
// {
// 	t_tokens	*newnode;
// 	t_tokens	*temp;

// 	if (thestack == NULL)
// 		return (0);
// 	newnode = malloc(sizeof(t_tokens));
// 	if (newnode == NULL)
// 	{
// 		write(2, "Error\n", 6);
// 		return (1);
// 	}
// 	newnode->token = tokens_split;
// 	newnode->next = NULL;
// 	if (*thestack == NULL)
// 		*thestack = newnode;
// 	else
// 	{
// 		temp = *thestack;
// 		while (temp->next != NULL)
// 			temp = temp->next;
// 		temp->next = newnode;
// 	}
// 	return (0);
// }
// /*returns last node of the ll*/
// t_tokens	*ft_lasttoken(t_tokens *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next != NULL)
// 		lst = lst->next;
// 	return (lst);
// }

// int	fill_ll(char *tokens_split, t_tokens *tokens)
// {
// 	t_tokens	*tmp;

// 	if (push(&tokens, tokens_split))
// 		return (1);
// 	tmp = ft_lasttoken(tokens);
// 	free(tmp->next);
// 	tmp->next = NULL;
// 	return (0);
// }
// int	init_tokens(t_tokens **tokens, char *inpt)
// {
// 	int	i;
// 	char	**tokens_split;

// 	i = 0;
// 	tokens_split = ft_split(inpt, ' ');
// 	while (tokens_split[i])
// 	{
// 		// printf(">>>>%s\n", tokens_split[i]);
// 		if (fill_ll(tokens_split[i], *tokens))
// 			return(write(2, "Error\n", 6));
// 		i++;	
// 	}
// 	free_2d(&tokens_split);
// 	return (0);
// }

// t_tokens	*init_firstphase(char *inpt)
// {
// 	t_tokens	*tokens;
// 	t_tokens	*tmp;

// 	tokens = malloc(sizeof(t_tokens));
// 	if (init_tokens(&tokens, inpt) != 0)
// 	{
// 		write(2, "Error\n", 6);
// 		return (NULL);
// 	}
// 	tmp = tokens;
// 	tokens = tokens->next;
// 	free(tmp);
// 	// tmp = ft_lasttoken(tokens);
// 	// tmp->next = tokens;
// 	return (tokens);
// }
