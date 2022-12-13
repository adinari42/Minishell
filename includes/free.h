/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adinari <adinari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:35:05 by slakner           #+#    #+#             */
/*   Updated: 2022/12/09 14:24:51 by adinari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "minishell.h"

void	free_split(char **splitret);
void	free_token_list(t_token *list);
void	free_token(t_token *token);
void	free_2d(char ***to_free);
void	free_strings(char *str, char **split1);
void	free_dlist(t_dlist *list);
void	free_char_arr(char **to_free);
void	free_kval(t_kval *kval);
void	free_parse(t_parse *parse);
void	free_pipes(t_token **pipes);
void	free_split_count(char **split, int count);
#endif