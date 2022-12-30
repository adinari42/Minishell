/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slakner <slakner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 20:14:43 by slakner           #+#    #+#             */
/*   Updated: 2022/12/30 20:15:11 by slakner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"


int	prnt_err(char *cmd, char *arg, char *errstr)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": `", 3);
	write(2, arg, ft_strlen(arg));
	write(2, "': ", 3);
	write(2, errstr, ft_strlen(errstr));
	write(2, "\n", 1);
	return (1);
}

int	prnt_err2(char *cmd, char *errstr)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	write(2, errstr, ft_strlen(errstr));
	write(2, "\n", 1);
	return (1);
}


int	print_builtin_error(char *builtin, char *dir)
{
	if (ft_strncmp(builtin, "cd", 3))
		access(dir, X_OK);
	write (2, "minishell: ", 11);
	write (2, builtin, ft_strlen(builtin));
	write (2, ":", 1);
	write (2, dir, ft_strlen(dir));
	if (errno == EACCES)
		write(2, "/", 1);
	write (2, ": ", 1);
	if (errno == EACCES)
		write(2, "permission denied\n", ft_strlen("permission denied\n"));
	else if (errno == ENOTDIR)
		write(2, "Not a directory\n", ft_strlen("Not a directory\n"));
	else if (errno == ENAMETOOLONG)
		write(2, "File name too long\n", ft_strlen("File name too long\n"));
	else if (errno == ENOENT)
		write(2, "No such file or directory\n",
			ft_strlen("No such file or directory\n"));
	return (0);
}
