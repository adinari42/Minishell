/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:35:05 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 01:01:25 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H
# include "minishell.h"

void	free_split(char **splitret);
void	free_token_list(t_token *list);
void	free_token_list_and_ptr(t_token **list);
void	free_token(t_token *token);
void	free_parse(t_parse *parse);
void	free_char_arr(char **to_free);
void	free_dlist(t_dlist *list);
void	free_kval(t_kval *kval);
void	free_pipes(t_token **pipes);
void	free_if_non_null(char *str);
#endif