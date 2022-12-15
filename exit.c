/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:15:15 by slakner           #+#    #+#             */
/*   Updated: 2022/12/09 20:31:40 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_value(int retval, t_dlist **env)
{
	free_dlist(*env);
	free(env);
	system("leaks minishell");
	exit(retval);
	return ;
}

void	free_and_exit(int signum, t_dlist **env)
{
	if (signum == SIGINT)
	{
		free_dlist(*env);
		free(env);
		system("leaks minishell");
		exit(0);
	}
	return ;
}
<<<<<<< Updated upstream
=======

// /* free all the allocated memory that needs to be freed before ending the program */
// void	free_globals(void)
// {
// 	if (g_env)
// 	{
// 		free_dlist(*g_env);
// 		free(g_env);
// 	}
// }
>>>>>>> Stashed changes
