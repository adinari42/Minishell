/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:01:42 by slakner           #+#    #+#             */
/*   Updated: 2022/12/29 18:06:39 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	nul(int signum)
{
	if (signum == SIGQUIT)
		rl_redisplay();
}

void	minishell_new_prompt(int signum)
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

void	heredoc_sigint_handler(int signum)
{
	// printf("%d\n", signum);
	if (signum == SIGINT)
	{
		// printf("%d\n", signum);
		g_stop = 1;
		//write(1, "\n", 1);
		// rl_replace_line("", 0);
		// rl_redisplay();
		write (2, "\n", 1);
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
	signal(SIGINT, heredoc_sigint_handler);;
	//signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, nul);
	tcgetattr(fd, &t_settings);
	//printf("%lx %lx\n", t_settings.c_lflag, t_settings.c_oflag);
	//t_settings.c_lflag |= ICANON;
	t_settings.c_lflag &=~ECHOCTL;
	//t_settings.c_oflag |=OCRNL;
	//printf("%lx %lx\n", t_settings.c_lflag, t_settings.c_oflag);
	// t_settings.c_cc[VMIN] = 1;
	// t_settings.c_cc[VTIME] = 0;
	tcsetattr(fd, 0, &t_settings);
}

int	error_code(int *err)
{
	static	int error_code;

	if (err)
		error_code = *err;
	return (error_code);
}

void	minishell_new_prompt_blocking(int signum)
{
	int err;

	err = 130;
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		error_code(&err);
	}
}

void	sigquit_blocking(int signum)
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

void	signals_blocking_command(void)
{
	struct termios		t_settings;

	signal(SIGINT, minishell_new_prompt_blocking);
	signal(SIGQUIT, sigquit_blocking);
	tcgetattr(1, &t_settings);
	// printf("ECHOCTL: %d %x \n", ECHOCTL, ECHOCTL);
	// printf("tcgetattr.c_lflag: %lu\n", t_settings.c_lflag);
	t_settings.c_lflag |=ECHOCTL;
	// printf("tcgetattr.c_lflag: %lu\n", t_settings.c_lflag);
	tcsetattr(1, 0, &t_settings);
}

// Ctrl-C: SIGINT
// Ctrl-\: SIGQUIT
void	init_signals(void)
{
	signal(SIGINT, minishell_new_prompt);
	signal(SIGQUIT, nul);
}
