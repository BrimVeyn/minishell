/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 08:53:03 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/29 10:30:02 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

char	*ms_find_var(t_env *denv, char *var)
{
	int		i;
	size_t	var_len;
	char	*value;

	i = 0;
	var_len = ft_strlen(var);
	value = NULL;
	while (denv->f_env[i])
	{
		if (ft_strlen(denv->f_env[i]) > var_len && !ft_strncmp(denv->f_env[i],
				var, var_len))
			value = ft_substr(denv->f_env[i], var_len, ft_strlen(denv->f_env[i])
					- var_len);
		i++;
	}
	return (value);
}

static void	cd_minus(t_env *denv)
{
	char	*oldpwd;
	int		index[2];
	char	*newpwd;
	char	*tmp;

	update_env(denv);
	oldpwd = denv->pwd;
	newpwd = ms_find_var(denv, "OLDPWD=");
	index[0] = ms_var_exist("PWD=", denv);
	index[1] = ms_var_exist("OLDPWD=", denv);
	if (!newpwd)
	{
		fd_printf(2, "minishell: cd: OLDPWD not set\n");
		g_exitno = 1;
		return ;
	}
	if (!ft_strncmp(newpwd, "~", 2))
	{
		tmp = ft_substr(newpwd, 1, ft_strlen(newpwd) - 1);
		newpwd = ft_strjoin(ft_strjoin_free(ft_strdup("/home/"),
					ft_strdup(denv->usr)), tmp);
		free(tmp);
	}
	if (index[1] != ERROR && ms_filetype(newpwd) != DIRECTORY)
	{
		fd_printf(2, "minishell: cd: %fs: No such file or directory\n", newpwd);
		free(newpwd);
		return ;
	}
	chdir(newpwd);
	if (index[0] != ERROR)
	{
		tmp = ft_strjoin("PWD=", newpwd);
		denv->f_env = ms_replace_value(denv->f_env, index[0], tmp);
		free(tmp);
	}
	if (index[1] != ERROR)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		denv->f_env = ms_replace_value(denv->f_env, index[1], tmp);
		free(tmp);
	}
	if (index[0] == ERROR && index[1] != ERROR)
		denv->f_env = del_var(denv->f_env, index[1]);
	else if (index[1] == ERROR)
	{
		tmp = ft_strjoin("OLDPWD=", oldpwd);
		denv->f_env = ms_join_tab(denv->f_env, tmp);
		free(tmp);
	}
	free(newpwd);
	g_exitno = 0;
}

void	b_cd(char **args, t_env *denv)
{
	int		index[2];
	char	current_directory[PATH_MAX];
	char	*newoldpwd;
	char	*tmp;

	newoldpwd = NULL;
	tmp = NULL;
	if (ms_tablen(args) > 2)
	{
		fd_printf(2, "minishell: cd: too many arguments\n");
		g_exitno = 1;
		return ;
	}
	else if (ms_tablen(args) == 1)
	{
		chdir(ms_getenv("HOME", denv));
		g_exitno = 0;
		return ;
	}
	if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		cd_minus(denv);
	else if (ms_filetype(args[1]) == DIRECTORY)
	{
		index[0] = ms_var_exist("PWD=", denv);
		index[1] = ms_var_exist("OLDPWD=", denv);
		if (index[0] != ERROR)
			newoldpwd = ft_strdup(denv->f_env[index[0]]);
		chdir(args[1]);
		getcwd(current_directory, sizeof(current_directory));
		if (index[0] != ERROR)
		{
			tmp = ft_strjoin("PWD=", current_directory);
			denv->f_env = ms_replace_value(denv->f_env, index[0], tmp);
			// free(tmp);
		}
		else if (index[0] == ERROR && index[1] != ERROR)
			denv->f_env = del_var(denv->f_env, index[1]);
		if (index[0] != ERROR && index[1] != ERROR)
		{
			tmp = ft_strjoin("OLD", newoldpwd);
			denv->f_env = ms_replace_value(denv->f_env, index[1], tmp);
			// free(tmp);
		}
		else if (newoldpwd)
		{
			tmp = ft_strjoin("OLD", newoldpwd);
			denv->f_env = ms_join_tab(denv->f_env, tmp);
			// free(tmp);
		}
		free(newoldpwd);
		free(tmp);
		g_exitno = 0;
	}
	else
	{
		fd_printf(2, "minishell: cd: %fs: No such file or directory\n",
			args[1]);
		g_exitno = 1;
	}
}
