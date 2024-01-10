/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 09:31:25 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/10 10:22:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>

char	*join_path(char *cmd, t_env *denv)
{
	int	i;
	char **paths;
	char *cmd_cpy;

	paths = ft_split(denv->path, ':');
	i = 0;
	while (paths[i])
	{
		cmd_cpy = ft_strjoin_s2(paths[i], ft_strjoin_s2("/", ft_strdup(cmd)));
		// printf("%s\n", cmd_cpy);
		if (!access(cmd_cpy, X_OK | F_OK))
		{
			free_tab(paths);
			free(cmd);
			return (cmd_cpy);
		}
		free(cmd_cpy);
		i++;
	}
	free_tab(paths);
	return(cmd);
}

void	ms_add_path(t_tok *tdata, t_env *denv)
{
	int i;

	i = 0;
	while (tdata->tokens[i])
	{
		if (tdata->type[i] == CMD)
			tdata->tokens[i][0] = join_path(tdata->tokens[i][0], denv);
		i++;
	}
}
