/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_h.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:26:03 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 14:50:14 by bvan-pae         ###   ########.fr       */
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

void	no_old_pwd(void)
{
	fd_printf(2, "minishell: cd: OLDPWD not set\n");
	g_exitno = 1;
}

void	cd_tild(char *newpwd, t_env *denv)
{
	char	*tmp;

	tmp = ft_substr(newpwd, 1, ft_strlen(newpwd) - 1);
	newpwd = ft_strjoin(ft_strjoin_free(ft_strdup("/home/"),
				ft_strdup(denv->usr)), tmp);
	free(tmp);
}

void	error_3(char *newpwd)
{
	fd_printf(2, "minishell: cd: %fs: No such file or directory\n", newpwd);
	free(newpwd);
}

void	no_pwd(char *newpwd, t_env *denv, int *index)
{
	char	*tmp;

	tmp = ft_strjoin("PWD=", newpwd);
	denv->f_env = ms_replace_value(denv->f_env, index[0], tmp);
	free(tmp);
}
