/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:14:00 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 21:12:09 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

t_dlist	**init_minishell(char **envp)
{
	t_dlist	**l_envp;

	init_term();
	l_envp = init_env_llist(envp);
	init_signals();
	return (l_envp);
}

void	reset_term_signals(void)
{
	init_term();
	init_signals();
}

void	init_term(void)
{
	struct termios	t_settings;

	tcgetattr(1, &t_settings);
	t_settings.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &t_settings);
}

t_dlist	**init_env_llist(char **envp)
{
	t_dlist	**l_envp;
	int		i;
	t_kval	*var;
	char	**tmp;

	if (!envp)
		return (NULL);
	i = 0;
	l_envp = malloc(sizeof(t_dlist *));
	*l_envp = NULL;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		var = malloc(sizeof(t_kval));
		var->key = ft_strdup(tmp[0]);
		var->val = ft_strdup(tmp[1]);
		free_split(tmp);
		lstadd_back(l_envp, lstnew(var));
		i++;
	}
	return (l_envp);
}

// Ctrl-C: SIGINT
// Ctrl-\: SIGQUIT
void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
