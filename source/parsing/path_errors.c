/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:01:11 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/07 15:20:54 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	no_such_file(char *cmd)
{
	if (access(cmd, F_OK) && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: No such file or directory\n", cmd);
		g_exitno = 127;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	is_a_directory(char *cmd)
{
	if (!access(cmd, X_OK) && ms_filetype(cmd) == DIRECTORY && ft_strchr(cmd,
			'/'))
	{
		fd_printf(2, "minishell: %fs: Is a directory\n", cmd);
		g_exitno = 126;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	command_not_found(char *cmd)
{
	if (!ft_strncmp(cmd, "", 2))
	{
		fd_printf(2, "'': command not found\n");
		g_exitno = 127;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	permission_denied(char *cmd)
{
	if (access(cmd, X_OK) && ms_filetype(cmd) == FAILE && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: Permission denied\n", cmd);
		g_exitno = 126;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}
