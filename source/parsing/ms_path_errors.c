/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_path_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:01:11 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 11:59:00 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	no_such_file(char *cmd, t_tok *tdata)
{
	(void)tdata;
	if (access(cmd, F_OK) && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: No such file or directory\n", cmd);
		// tdata->exitno = 127 << 8;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	is_a_directory(char *cmd, t_tok *tdata)
{
	if (!access(cmd, X_OK) && ms_filetype(cmd) == DIRECTORY && ft_strchr(cmd,
			'/'))
	{
		fd_printf(2, "minishell: %fs: Is a directory\n", cmd);
		tdata->exitno = 126 << 8;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	command_not_found(char *cmd, t_tok *tdata)
{
	(void)tdata;
	if (!ft_strncmp(cmd, "", 2))
	{
		fd_printf(2, "'': command not found\n");
		// tdata->exitno = 127 << 8;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}

int	permission_denied(char *cmd, t_tok *tdata)
{
	if (access(cmd, X_OK) && ms_filetype(cmd) == FAILE && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: Permission denied\n", cmd);
		tdata->exitno = 126 << 8;
		return (free(cmd), ERROR);
	}
	return (TRUE);
}
