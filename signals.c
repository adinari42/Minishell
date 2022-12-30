/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:01:42 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 21:10:23 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		rl_redisplay();
}

void	sigint_handler(int signum)
{
	int	err;

	err = 1;
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		error_code(&err);
	}
}

void	signals_blocking_command(void)
{
	struct termios		t_settings;

	signal(SIGINT, sigint_handler_blocking);
	signal(SIGQUIT, sigquit_handler_blocking);
	tcgetattr(1, &t_settings);
	t_settings.c_lflag |= ECHOCTL;
	tcsetattr(1, 0, &t_settings);
}

void	sigint_handler_blocking(int signum)
{
	int	err;

	err = 130;
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		error_code(&err);
	}
}

void	sigquit_handler_blocking(int signum)
{
	int	err;

	err = 131;
	if (signum == SIGQUIT)
	{
		printf("Quit: 3\n");
		rl_redisplay();
		error_code(&err);
	}
}
