/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:15:15 by slakner           #+#    #+#             */
/*   Updated: 2022/11/25 12:49:27 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_value(int retval)
{
	free_globals();
	system("leaks minishell");
	exit(retval);
	return ;
}

void	free_and_exit(int signum)
{
	free_globals(void);
	system("leaks minishell");
}

/* free all the allocated memory that needs to be freed before ending the program */
void	free_globals(void)
{
	free_dlist(g_env);
	free(g_env);
}
