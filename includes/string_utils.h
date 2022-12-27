/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:12:20 by slakner           #+#    #+#             */
/*   Updated: 2022/12/19 20:56:10 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_UTILS_H
# include "minishell.h"

int		is_whitespace(const char *c);
char	*ft_strjoin_free_str1(char *str1, char *str2);
int		count_split_elems(char **arr);

#endif
