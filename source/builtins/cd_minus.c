/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:26:03 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 13:44:21 by nbardavi         ###   ########.fr       */
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

void	cd_minus_bothset(t_env *denv, char *oldpwd, char *pwd)
{
	char	*newpwd;
	char	*newoldpwd;

	if (ms_var_exist("PWD", denv) != ERROR && ms_var_exist("OLDPWD",
			denv) != ERROR)
	{
		chdir(oldpwd);
		newpwd = ft_sprintf("%fs%fs", "PWD=", oldpwd);
		newoldpwd = ft_sprintf("%fs%fs", "OLDPWD=", pwd);
		denv->f_env = ms_replace_value(denv->f_env, ms_var_exist("PWD", denv),
				newpwd);
		denv->f_env = ms_replace_value(denv->f_env, ms_var_exist("OLDPWD",
					denv), newoldpwd);
		return (free(newpwd), free(newoldpwd));
	}
}

void	cd_minus_oldpwdnotset(char *oldpwd)
{
	if (oldpwd == NULL)
	{
		fd_printf(2, "minishell: cd: OLDPWD not set\n");
		g_exitno = 1 << 8;
	}
}

int	no_args(char **args, t_env *denv)
{
	char	*tmp;

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

void	cd_minus(t_env *denv)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ms_find_var(denv, "PWD");
	oldpwd = ms_find_var(denv, "OLDPWD");
	if (pwd)
		pwd = ft_substr_free(pwd, 1, ft_strlen(pwd));
	if (oldpwd)
		oldpwd = ft_substr_free(oldpwd, 1, ft_strlen(oldpwd));
	cd_minus_bothset(denv, oldpwd, pwd);
	cd_minus_oldpwdnotset(oldpwd);
	return (free(pwd), free(oldpwd));
}
