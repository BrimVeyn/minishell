/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:50:19 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 14:54:16 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

static void	cd_minus_h(t_env *denv, int *index, char *newpwd, char *oldpwd)
{
	if (index[0] != ERROR)
		no_pwd(newpwd, denv, index);
	if (index[1] != ERROR)
		oldpwdt(oldpwd, denv, index);
	if (index[0] == ERROR && index[1] != ERROR)
		denv->f_env = del_var(denv->f_env, index[1]);
	else if (index[1] == ERROR)
		nooldpwd(oldpwd, denv);
}

static void	cd_minus(t_env *denv)
{
	char	*oldpwd;
	int		index[2];
	char	*newpwd;
	char	*tmp;

	tmp = NULL;
	oldpwd = denv->pwd;
	newpwd = ms_find_var(denv, "OLDPWD=");
	index[0] = ms_var_exist("PWD=", denv);
	index[1] = ms_var_exist("OLDPWD=", denv);
	if (!newpwd)
		return (no_old_pwd());
	if (!ft_strncmp(newpwd, "~", 2))
		cd_tild(newpwd, denv);
	if (index[1] != ERROR && ms_filetype(newpwd) != DIRECTORY)
		return (error_3(newpwd));
	chdir(newpwd);
	cd_minus_h(denv, index, newpwd, oldpwd);
	free(newpwd);
	g_exitno = 0;
}

void	valid_file(char *newoldpwd, char **args, t_env *denv, int *index)
{
	char	current_directory[PATH_MAX];
	char	*tmp;

	tmp = NULL;
	index[0] = ms_var_exist("PWD=", denv);
	index[1] = ms_var_exist("OLDPWD=", denv);
	if (index[0] != ERROR)
		newoldpwd = ft_strdup(denv->f_env[index[0]]);
	getcwd(current_directory, sizeof(current_directory));
	if (index[0] != ERROR)
	{
		tmp = ft_strjoin("PWD=", current_directory);
		denv->f_env = ms_replace_value(denv->f_env, index[0], tmp);
	}
	else if (index[0] == ERROR && index[1] != ERROR)
		denv->f_env = del_var(denv->f_env, index[1]);
	if (index[0] != ERROR && index[1] != ERROR)
		opt_1(newoldpwd, tmp, denv, index);
	else if (newoldpwd)
		opt_2(newoldpwd, tmp, denv);
	g_exitno = 0;
	return (chdir(args[1]), free(newoldpwd), free(tmp));
}

void	b_cd(char **args, t_env *denv)
{
	int		index[2];
	char	*newoldpwd;
	char	*tmp;

	newoldpwd = NULL;
	tmp = NULL;
	if (too_many_args(args) == ERROR || no_args(args, denv) == TRUE)
		return ;
	if (ft_strlen(args[1]) == 1 && args[1][0] == '-')
		cd_minus(denv);
	else if (ms_filetype(args[1]) == DIRECTORY)
		valid_file(newoldpwd, args, denv, index);
	else
		error_1(args);
}
