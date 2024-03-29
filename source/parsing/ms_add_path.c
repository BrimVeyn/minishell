/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_add_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:57:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/05 13:46:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_tab(int *pos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("W_POS[%d] = %d\n", i, pos[i]);
		i++;
	}
}

int	ms_filetype(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (TRUE);
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
		|| !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd,
			"robin"))
		return (TRUE);
	return (ERROR);
}

char	*join_path(char *cmd, t_env *denv, t_tok *tdata)
{
	int		i;
	char	**paths;
	char	*cmd_cpy;
	char	*temp;

	i = 0;
	if (!access(cmd, X_OK) && ms_filetype(cmd) == FAILE)
		return (cmd);
	temp = check_file(cmd, tdata);
	if (ft_strcmp(temp, cmd))
		return (free(cmd), temp);
	paths = ft_split(denv->path, ':');
	while (paths[i])
	{
		cmd_cpy = ft_strjoin_s2(paths[i], ft_strjoin_s2("/", ft_strdup(cmd)));
		if (!access(cmd_cpy, X_OK) && ms_filetype(cmd_cpy) == FAILE)
			return (free_tab(paths), free(cmd), cmd_cpy);
		free(cmd_cpy);
		i++;
	}
	if (permission_denied(cmd, tdata) == ERROR)
		return (free_tab(paths), ft_strdup("IGNORE"));
	fd_printf(2, "%fs: command not found\n", cmd);
	return (free_tab(paths), free(cmd), ft_strdup("WRONG"));
}

void	ms_add_path(t_tok *tdata, t_env *denv, int index)
{
	int	j;

	j = 0;
	if (ms_wltoken(tdata->tokens[index][j]) == ERROR
		|| ft_strncmp(tdata->tok_copy[index][j], tdata->tokens[index][j],
			ft_strlen(tdata->tok_copy[index][j])))
	{
		while (ms_wlcmdtok(tdata->tokens[index][j]) == TRUE)
		{
			if (!tdata->tokens[index][j + 1] || !tdata->tokens[index][j + 2])
				break ;
			j += 2;
		}
		if (ms_check_builtin(tdata->tokens[index][j]) == TRUE)
			tdata->type[index][j] = BUILTIN;
		else if (tdata->type[index][j] == CMD)
		{
			tdata->tokens[index][j] = join_path(tdata->tokens[index][j], denv,
					tdata);
			if (!ft_strncmp(tdata->tokens[index][j], "WRONG", 5))
				tdata->type[index][j] = WRONG;
			if (!ft_strncmp(tdata->tokens[index][j], "IGNORE", 5))
				tdata->type[index][j] = IGNORE;
		}
	}
}
