/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:31:33 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 01:20:19 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# include "minishell.h"

int		token_type(char *c);
char	*non_word_tknstr(char *bashcmd, size_t *i);
t_token	**read_tokens(char *bashcmd);
t_token	**tokenize(char *cmd);
t_token	**merge_word_strings(t_token **cmd_line);
#endif