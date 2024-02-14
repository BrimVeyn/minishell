/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:50:19 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 17:21:17 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <linux/limits.h>
#include <unistd.h>

extern int	g_exitno;

int	too_many_args(char **args)
{
	if (ms_tablen(args) > 2)
	{
		fd_printf(2, "minishell: cd: too many arguments\n");
		g_exitno = 1 << 8;
		return (TRUE);
	}
	return (ERROR);
}

void	cd_oldandpwdset(t_env *denv, char *arg, char *pwd)
{
	char	*newpwd;
	char	*newoldpwd;
	char	cdir[PATH_MAX];

	if (ms_var_exist("PWD", denv) != ERROR && ms_var_exist("OLDPWD",
			denv) != ERROR)
	{
		chdir(arg);
		getcwd(cdir, PATH_MAX);
		newpwd = ft_strdup(cdir);
		newoldpwd = ft_strdup(pwd);
		newpwd = ft_sprintf("%fs%s", "PWD=", newpwd);
		newoldpwd = ft_sprintf("%fs%s", "OLDPWD=", newoldpwd);
		denv->f_env = ms_replace_value(denv->f_env, ms_var_exist("PWD", denv),
				newpwd);
		denv->f_env = ms_replace_value(denv->f_env, ms_var_exist("OLDPWD",
					denv), newoldpwd);
		return (free(newpwd), free(newoldpwd));
	}
}

void	update_dir(t_env *denv, char *arg)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ms_find_var(denv, "PWD");
	oldpwd = ms_find_var(denv, "OLDPWD");
	if (pwd)
		pwd = ft_substr_free(pwd, 1, ft_strlen(pwd));
	if (oldpwd)
		oldpwd = ft_substr_free(oldpwd, 1, ft_strlen(oldpwd));
	cd_oldandpwdset(denv, arg, pwd);
	if (ms_var_exist("PWD", denv) == ERROR || ms_var_exist("OLDPWD",
			denv) == ERROR)
		chdir(arg);
	free(pwd);
	free(oldpwd);
}

void	cd_nosuchfile(char **args)
{
	fd_printf(2, "minishell: cd: %fs: No such file or directory\n", args[1]);
	g_exitno = 1 << 8;
}

void	b_cd(char **args, t_env *denv)
{
	if (too_many_args(args) == TRUE || no_args(args, denv) == TRUE)
		return ;
	if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		cd_minus(denv);
	else if (ms_filetype(args[1]) == DIRECTORY)
		update_dir(denv, args[1]);
	else
		cd_nosuchfile(args);
}
