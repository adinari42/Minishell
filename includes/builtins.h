/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:26:20 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 20:37:45 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

int		exec_echo(t_token *token, t_dlist *env);
int		exec_cd(t_token *token, t_dlist *env, t_pipe *data);
int		exec_pwd(t_token *token, t_dlist *env);
int		exec_export(t_token *token, t_dlist *env);
int		exec_unset(t_token *token, t_dlist *env);
int		exec_env(t_token *token, t_dlist *env);
void	exec_exit(t_token *token, t_dlist **env, t_pipe *data);

int		update_var(char *varname, char *value, t_dlist *env);
int		is_builtin(char *str);
t_kval	*extract_keyvalue_unquoted(t_token *tkn);
void	write_export_var(t_kval *content, t_dlist *env);
void	exit_if_not_numeric(t_token *tkn, t_dlist **env);

#endif