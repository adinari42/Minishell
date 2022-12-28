/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephanie.lakner <stephanie.lakner@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:01:42 by slakner           #+#    #+#             */
/*   Updated: 2022/12/28 21:56:08 by stephanie.l      ###   ########.fr       */
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
	if (signum == SIGINT)
	{
		write (1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
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
	printf("Returning err! %d\n", error_code);
	return (error_code);
}

void	minishell_new_prompt_blocking(int signum)
//void	sigint_blocking(int signum, t_pipe *data)
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
	// struct sigaction	sigint_action;
	// struct sigaction	old_action;

	// sigint_action.sa_handler = sigint_blocking;
	// sigemptyset(&sigint_action.sa_mask);
	// if (old_action.sa_handler != SIG_IGN)
	// 	sigaction(SIGINT, &sigint_action, NULL);
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
