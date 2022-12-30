/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:14:05 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 20:17:28 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# include "minishell.h"

int		error_code(int *err);
int		print_builtin_error(char *builtin, char *dir);
int		prnt_err2(char *cmd, char *errstr);

#endif