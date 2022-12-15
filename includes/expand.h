/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:30:20 by slakner           #+#    #+#             */
/*   Updated: 2022/12/09 18:35:03 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

/*expandvalue.c*/
char	*value_expand(char **envp, char *var);
char	*expand_value(char *str, t_dlist *env);
void	check_value(t_token *list, t_dlist *env);
void	free_2d(char ***to_free);
void	free_strings(char *str, char **split1);
char	*add_space(char *tmp, char *res);
char	*join_to_res(char *tmp, char **split2, char *res, int j, char **envp);
#endif