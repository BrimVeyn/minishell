/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 09:31:25 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 10:12:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <unistd.h>
#include <sys/stat.h>

int	filetype(char *path)	
{
	struct stat path_stat;

	stat(path, &path_stat);
	if (S_ISREG(path_stat.st_mode)) 
	{
		return (FAILE);
		// printf("%s est un fichier régulier.\n", path);
	} 
	else 
	{
		return(ERROR);
		// printf("%s est un type de fichier non pris en charge.\n", path);
	}
}

int	ms_check_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo") ||
		!ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") ||
		!ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit"))
		return (TRUE);
	return (ERROR);
}


char	*join_path(char *cmd, t_env *denv)
{
	int	i;
	char **paths;
	char *cmd_cpy;

	i = 0;
	// printf("This is the cmd : %s\n", cmd);
	if (!access(cmd, X_OK) && filetype(cmd) == FAILE)
		return (cmd);
	paths = ft_split(denv->path, ':');
	if (!ft_strncmp(cmd, "", 2))
    {
		fd_printf(2, "'': command not found\n");
		return (NULL);
    }
	while (paths[i])
	{
		cmd_cpy = ft_strjoin_s2(paths[i], ft_strjoin_s2("/", ft_strdup(cmd)));
		if (!access(cmd_cpy, X_OK) && filetype(cmd_cpy) == FAILE)
		{
			free_tab(paths);
			free(cmd);
			return (cmd_cpy);
		}
		free(cmd_cpy);
		i++;
	}
	free_tab(paths);
	fd_printf(2, "%fs: command not found\n", cmd);
	return(free(cmd), ft_strdup("WRONG"));
}

void	ms_add_path(t_tok *tdata, t_env *denv)
{
	int		i;

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
					tdata->type[i] = WRONG;
            }
        }
		i++;
	}
}
