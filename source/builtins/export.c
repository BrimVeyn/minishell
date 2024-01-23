/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:15:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 13:00:43 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **join_tab(char **tab, char *str)
{
	char **new;
	int	i;

	i = -1;
	new = ft_calloc(ms_tablen(tab) + 2, sizeof(char *));
	while (tab[++i])
		new[i] = ft_strdup(tab[i]);
	new[i] = ft_strdup(str);
	return (free_tab(tab), new);
}

int	var_exist(char *var, t_env *denv)
{
	char *tmp;
	int	i;

	i = 0;
	tmp = ms_cut_at(var, '=');
	while (denv->f_env[i])
	{
		if (!ft_strncmp(denv->f_env[i], tmp, ft_strlen(tmp)))
		{
			ft_printf("ARLEADY EXIST");
			return (TRUE);
		}
	}
	return (ERROR);
}

void	b_export(char **args, t_env *denv)
{
	int i = 0;
	char	*tmp;

	tmp = NULL;
	while (args[i])
	{
		if (i > 0 && args[i])
		{
			tmp = ft_strchr(args[i], '=');
			if (tmp && var_exist(args[i], denv) == ERROR)
			{
				denv->f_env = join_tab(denv->f_env, args[i]);
			}
		}
		i++;
	}
}
