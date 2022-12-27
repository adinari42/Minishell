/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:30:29 by slakner           #+#    #+#             */
/*   Updated: 2022/12/13 21:33:30 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# include "minishell.h"

t_dlist	**init_env_llist(char **envp);
void	init_term();
t_dlist	**init_minishell(char **envp);
void	reset_term_signals(void);
#endif
