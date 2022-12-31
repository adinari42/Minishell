/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:25:04 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 03:14:43 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "minishell.h"

int	handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env);
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data);
int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env);

#endif