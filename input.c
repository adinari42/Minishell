/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 22:17:41 by slakner           #+#    #+#             */
/*   Updated: 2022/12/31 00:35:15 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	handle_input(t_token **plist, t_pipe *data, t_dlist **env)
{
	int		i;

	i = 0;
	data->cmd_pos = count_pipes(plist);
	while (plist[i])
	{
		handle_single_pipe(plist[i], data, env, i);
		i++;
	}
	data->error_code = WEXITSTATUS(data->status);
	if (error_code(NULL))
	{
		data->error_code = error_code(NULL);
		i = 0;
		error_code(&i);
	}
	return (data->status);
}

char	*get_input_line(t_dlist **env, t_pipe *data, int stdin_restore)
{
	char	*inpt;

	if (isatty(stdin_restore))
		inpt = readline("Minishell$ ");
	else
	{	
		inpt = get_next_line(0);
		if (!inpt)
			exit(data->error_code);
		inpt = ft_strtrim(inpt, "\n");
	}
	if (!inpt)
		free_and_exit(SIGINT, env);
	add_history(inpt);
	if (is_empty_inpt(inpt))
		return (NULL);
	return (inpt);
}
