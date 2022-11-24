/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 21:15:15 by slakner           #+#    #+#             */
/*   Updated: 2022/11/24 14:49:36 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int free_and_exit()
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
