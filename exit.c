/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:15:15 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 05:33:32 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_value(int retval, t_dlist **env)
{
	free_dlist(*env);
	free(env);
	exit(retval);
	return ;
}

void	free_and_exit(int signum, t_dlist **env)
{
	if (signum == SIGINT)
	{
		free_dlist(*env);
		free(env);
		exit(0);
	}
	return ;
}
