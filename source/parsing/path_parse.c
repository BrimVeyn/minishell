/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:25:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 15:27:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	ms_filetype(char *path)
{
	struct stat	path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode))
		return (FAILE);
	else if (S_ISDIR(path_stat.st_mode))
		return (DIRECTORY);
	else if (ft_strchr(path, '/'))
		return (TRUE);
	else
		return (ERROR);
}

int	ms_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd,
			"unset") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "echo") 
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "robin"))
		return (TRUE);
	return (ERROR);
}

char	*join_path(char *cmd, t_env *denv)
{
	int		i;
	char	**paths;
	char	*cmd_cpy;

	i = 0;
	if (cmd[0] == -19)
	{
		return (free(cmd), ft_strdup("WRONG"));
	}
	if (!access(cmd, X_OK) && ms_filetype(cmd) == FAILE)
		return (cmd);
	if (access(cmd, X_OK) && ms_filetype(cmd) == TRUE)
	{
		fd_printf(2, "minishell: %fs: No such file or directory\n", cmd);
		g_exitno = 127;
		return (free(cmd), ft_strdup("WRONG"));
	}
	if (!access(cmd, X_OK) && ms_filetype(cmd) == DIRECTORY && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: Is a directory\n", cmd);
		g_exitno = 126;
		return (free(cmd), ft_strdup("WRONG"));
	}
	paths = ft_split(denv->path, ':');
	if (!cmd)
		return (ft_strdup("WRONG"));
	if (!ft_strncmp(cmd, "", 2))
	{
		fd_printf(2, "'': command not found\n");
		g_exitno = 127;
		return (free_tab(paths), free(cmd), ft_strdup("WRONG"));
	}
	while (paths[i])
	{
		cmd_cpy = ft_strjoin_s2(paths[i], ft_strjoin_s2("/", ft_strdup(cmd)));
		if (!access(cmd_cpy, X_OK) && ms_filetype(cmd_cpy) == FAILE)
			return (free_tab(paths), free(cmd), cmd_cpy);
		free(cmd_cpy);
		i++;
	}
	free_tab(paths);
	if (access(cmd, X_OK) && ms_filetype(cmd) == FAILE && ft_strchr(cmd, '/'))
	{
		fd_printf(2, "minishell: %fs: Permission denied\n", cmd);
		g_exitno = 126;
		return (free(cmd), ft_strdup("WRONG"));
	}
	fd_printf(2, "%fs: command not found\n", cmd);
	g_exitno = 127;
	return (free(cmd), ft_strdup("WRONG"));
}

void	ms_add_path(t_tok *tdata, t_env *denv)
{
	int	i;

	i = 0;
	while (tdata->tokens[i])
	{
		if (tdata->type[i] == CMD)
		{
			if (ms_check_builtin(tdata->tokens[i][0]) == TRUE)
				tdata->type[i] = BUILTIN;
			else
			{
				tdata->tokens[i][0] = join_path(tdata->tokens[i][0], denv);
				if (!ft_strncmp(tdata->tokens[i][0], "WRONG", 5))
				{
					// g_exitno = 127;
					tdata->type[i] = WRONG;
				}
			}
		}
		i++;
	}
}
