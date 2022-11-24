/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:15:15 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 15:29:25 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_and_exit(int signum)
{
	if (signum == SIGINT)
	{
		free_globals();
		system("leaks minishell");
		exit(0);
	}
	return ;
}

/* free all the allocated memory that needs to be freed before ending the program */
void	free_globals(void)
{
	if (g_env)
	{
		free_dlist(*g_env);
		free(g_env);
	}
}
