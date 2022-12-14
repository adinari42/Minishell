/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:54:34 by slakner           #+#    #+#             */
/*   Updated: 2022/12/09 21:04:07 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	**envp_parse(char **envp);
char	*extract_varname_quoted(char *tokenstr);
char	*extract_value(char *tokenstr);
int		var_in_env(char *varname, t_dlist *env);
int		display_env(t_dlist *env);
int		num_vars_env(t_dlist *env);
char	**env_list_to_char_arr(t_dlist **env);
int		prnt_err(char *cmd, char *arg, char *errstr);
int		valid_identifier(char *varname);
char	*get_value_from_key(t_dlist *var, char *varname);

#endif