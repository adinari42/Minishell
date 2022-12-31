/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:58:32 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:34:16 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	heredoc_nul(int signum)
{
	(void) signum;
}

void	heredoc_sigint_handler(int signum)
{
	struct termios	t_settings;
	int				err;

	err = 130;
	if (signum == SIGINT)
	{
		g_stop = 1;
		tcgetattr(0, &t_settings);
		t_settings.c_lflag &= ~ECHOCTL;
		t_settings.c_iflag |= O_NONBLOCK;
		tcsetattr(0, TCSANOW, &t_settings);
		write(0, "\n", 1);
		close(0);
		error_code(&err);
	}
}

void	heredoc_sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		g_stop = 1;
	}
}

void	heredoc_signals(int fd)
{
	struct termios	t_settings;

	signal(SIGINT, SIG_DFL);
	signal(SIGINT, heredoc_sigint_handler);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, heredoc_nul);
	tcgetattr(fd, &t_settings);
	t_settings.c_lflag &= ~ECHOCTL;
	tcsetattr(fd, 0, &t_settings);
}
