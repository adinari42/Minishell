/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:30:29 by slakner           #+#    #+#             */
/*   Updated: 2022/12/04 20:22:18 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# include "minishell.h"

int		init_env(char **envp);
int		init_env_llist(char **envp);
void	init_term();
void	init_minishell(char **envp);