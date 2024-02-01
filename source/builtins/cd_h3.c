/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_h3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:27:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 10:28:10 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	opt_1(char *newoldpwd, char *tmp, t_env *denv, int *index)
{
	tmp = ft_strjoin("OLD", newoldpwd);
	denv->f_env = ms_replace_value(denv->f_env, index[1], tmp);
}

void	opt_2(char *newoldpwd, char *tmp, t_env *denv, int *index)
{
	tmp = ft_strjoin("OLD", newoldpwd);
	denv->f_env = ms_join_tab(denv->f_env, tmp);
}

void	error_1(char **args)
{
	fd_printf(2, "minishell: cd: %fs: No such file or directory\n", args[1]);
	g_exitno = 1;
}
