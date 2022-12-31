/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:30:20 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 03:17:22 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

char	*value_expand(char **envp, char *var);
char	*expand_value(char *str, t_dlist *env, t_pipe *data);
void	check_value(t_token *list, t_dlist *env, t_pipe *data);
void	free_2d(char ***to_free);
void	free_strings(char *str, char **split1);
char	*add_space(char *tmp, char *res);
#endif