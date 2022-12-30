/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:26:20 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 19:28:08 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		is_builtin(char *str);
int		exec_echo(t_token *token, t_dlist *env);
int		exec_cd(t_token *token, t_dlist *env, t_pipe *data);
int		exec_pwd(t_token *token, t_dlist *env);
int		exec_export(t_token *token, t_dlist *env);
int		exec_unset(t_token *token, t_dlist *env);
int		exec_env(t_token *token, t_dlist *env);
void	exec_exit(t_token *token, t_dlist **env, t_pipe *data);
int		builtin_plausible(t_token *token, char *builtin);
int		print_builtin_error(char *builtin, char *dir);
int		prnt_err2(char *cmd, char *errstr);

#endif