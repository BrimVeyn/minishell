/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_replace_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:31:29 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 17:31:45 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ms_replace_value(char **f_env, int index, char *arg)
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
		new[i++] = ft_strdup(arg);
	while (f_env[i])
	{
		new[i] = ft_strdup(f_env[i]);
		i++;
	}
	return (free_tab(f_env), new);
}
