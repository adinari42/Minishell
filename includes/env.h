/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 20:54:34 by slakner           #+#    #+#             */
/*   Updated: 2022/11/25 13:38:37 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

char	**envp_parse(char **envp);
char	*extract_varname_quoted(char *tokenstr);
char	*extract_value(char *tokenstr);
int		var_in_env(char *varname);
int		display_env(void);
int		num_vars_env(void);
char	**env_list_to_char_arr(t_dlist **env);

#endif