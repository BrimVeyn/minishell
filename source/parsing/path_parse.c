/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:25:26 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:21:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	ms_filetype(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat))
		return (ERROR);
	if (S_ISREG(path_stat.st_mode))
		return (FAILE);
	else if (S_ISDIR(path_stat.st_mode))
		return (DIRECTORY);
	else
		return (ERROR);
}

int	ms_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd,
			"unset") || !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd"))
		return (TRUE);
	return (ERROR);
}

char	*join_path(char *cmd, t_env *denv)
{
	int		i;
	char	**paths;
	char	*cmd_cpy;

	i = 0;
	if (!access(cmd, X_OK) && ms_filetype(cmd) == FAILE)
		return (cmd);
	paths = ft_split(denv->path, ':');
	if (!ft_strncmp(cmd, "", 2))
	{
		fd_printf(2, "'': command not found\n");
		return (free(cmd), ft_strdup("WRONG"));
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
	fd_printf(2, "%fs: command not found\n", cmd);
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
					g_exitno = 127;
					tdata->type[i] = WRONG;
				}
			}
		}
		i++;
	}
}
