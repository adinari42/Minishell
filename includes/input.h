/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:10:47 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:36:00 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H
# include "minishell.h"

int		handle_input(t_token **plist, t_pipe *data, t_dlist **env);
char	*get_input_line(t_dlist **env, t_pipe *data, int stdin_restore);

#endif