/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 20:24:05 by slakner           #+#    #+#             */
/*   Updated: 2022/12/24 18:51:38 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "minishell.h"

int		parse(t_token **list, t_pipe *data);
int		is_empty_inpt(char *inpt);
int		check_pipes(t_token *tkn);
t_token	*remove_spaces(t_token *list);
#endif