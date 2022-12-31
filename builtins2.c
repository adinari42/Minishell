/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 19:53:54 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 03:37:34 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	exec_pwd(t_token *list, t_dlist *env)
{
	t_token	*tkn;
	char	pwd[1024];

	(void) env;
	tkn = list;
	tkn = skip_spaces(tkn);
	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	return (0);
}

int	exec_env(t_token *list, t_dlist *env)
{
	t_token	*tkn;

	tkn = list;
	tkn = skip_spaces(tkn);
	if (tkn)
	{
		printf("env: %s: No such file or directory\n", tkn->next->str);
		return (1);
	}
	display_env(env);
	return (0);
}

void	exec_exit(t_token *list, t_dlist **env, t_pipe *data)
{
	t_token	*tkn;

	tkn = list;
	tkn = skip_spaces(tkn);
	if (tkn)
	{
		write(2, "exit\n", 5);
		exit_if_not_numeric(tkn, env);
		data->error_code = ft_atoi(tkn->str);
		tkn = skip_spaces(tkn);
		if (tkn && tkn->type != SPACE_TKN)
		{
			prnt_err2("exit", "too many arguments");
			data->error_code = 1;
			return ;
		}
	}
	exit_with_value(data->error_code, env);
}

void	exit_if_not_numeric(t_token *tkn, t_dlist **env)
{
	char	*tokenstr;

	tokenstr = tkn->str;
	if (!*tokenstr)
	{
		prnt_err("exit", "tkn->str", "numeric argument required");
		exit_with_value(255, env);
	}
	while (*(tokenstr))
	{
		if (!ft_isdigit(*tokenstr))
		{
			prnt_err("exit", "tkn->str", "numeric argument required");
			exit_with_value(255, env);
		}
		tokenstr ++;
	}
}
