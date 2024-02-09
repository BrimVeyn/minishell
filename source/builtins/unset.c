/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:53:41 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 09:57:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_var_exist(char *var, t_env *denv)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ms_cut_at(ft_strdup(var), '=');
	while (denv->f_env[i])
	{
		if (!ft_strncmp(denv->f_env[i], tmp, ft_strlen(tmp)))
			return (free(tmp), i);
		i++;
	}
	return (free(tmp), ERROR);
}

char	**del_var(char **f_env, int index)
{
	char	**new;
	int		i;

	new = ft_calloc(ms_tablen(f_env) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (f_env[i] && i != index)
	{
		new[i] = ft_strdup(f_env[i]);
		i++;
	}
	if (i == index)
		i++;
	while (f_env[i])
	{
		new[i - 1] = ft_strdup(f_env[i]);
		i++;
	}
	return (free_tab(f_env), new);
}

void	b_unset(char **args, t_env *denv)
{
	int	i;
	int	index;

	i = 0;
	while (args[i])
	{
		if (i > 0 && args[i])
		{
			index = ms_var_exist(args[i], denv);
			if (index != ERROR)
				denv->f_env = del_var(denv->f_env, index);
		}
		i++;
	}
}
