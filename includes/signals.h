/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:00:23 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 03:20:09 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

void	sigquit_handler(int signum);
void	sigint_handler(int signum);
void	signals_blocking_command(void);
void	sigint_handler_blocking(int signum);
void	sigquit_handler_blocking(int signum);
void	heredoc_signals(int fd);
#endif