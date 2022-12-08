/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 20:49:58 by slakner           #+#    #+#             */
/*   Updated: 2022/12/08 16:46:33 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# include "minishell.h"

t_token	**list_to_pipes(t_token *list);
t_token	*cut_at_pipe(t_token *list, t_token **pipes, int i);
int		count_pipes(t_token **pipes);

#endif