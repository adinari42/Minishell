/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:01:42 by slakner           #+#    #+#             */
/*   Updated: 2022/11/27 14:43:56 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_new_prompt(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	nul(int signum)
{
	(void) signum;
}

// Ctrl-C: SIGINT
// Ctrl-\: SIGQUIT
void	init_signals(void)
{
	signal(SIGINT, minishell_new_prompt);
	signal(SIGQUIT, nul);
}
