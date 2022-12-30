/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:25:04 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 22:26:45 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H
# include "minishell.h"

int	handle_builtinstr(t_token *list, t_pipe *data, int i, t_dlist **env);
int	handle_builtin(t_token *list, t_dlist **env, t_pipe *data);
int	handle_command(t_pipe *data, t_token **cmd_line, int i, t_dlist **env);

#endif