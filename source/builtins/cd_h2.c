/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_h2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:26:36 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 11:25:07 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	oldpwdt(char *oldpwd, char *tmp, t_env *denv, int *index)
{
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	denv->f_env = ms_replace_value(denv->f_env, index[1], tmp);
	free(tmp);
}

void	nooldpwd(char *tmp, char *oldpwd, t_env *denv)
{
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	denv->f_env = ms_join_tab(denv->f_env, tmp);
	free(tmp);
}

void	fill_this(t_env *denv, char *oldpwd, char *newpwd, int *index)
{
	oldpwd = denv->pwd;
	newpwd = ms_find_var(denv, "OLDPWD=");
	index[0] = ms_var_exist("PWD=", denv);
	index[1] = ms_var_exist("OLDPWD=", denv);
}

int	too_many_args(char **args)
{
	if (ms_tablen(args) > 2)
	{
		fd_printf(2, "minishell: cd: too many arguments\n");
		g_exitno = 1;
		return (ERROR);
	}
	return (TRUE);
}

int	no_args(char **args, t_env *denv)
{
	char *tmp;

	if (ms_tablen(args) == 1)
	{
		tmp = ms_getenv(ft_strdup("HOME"), denv);
		chdir(tmp);
		free(tmp);
		g_exitno = 0;
		return (TRUE);
	}
	return (ERROR);
}
