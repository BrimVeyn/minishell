/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_join_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:24:43 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 09:52:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ms_join_tab(char **tab, char *str)
{
	char	**new;
	int		i;

	i = -1;
	new = ft_calloc(ms_tablen(tab) + 2, sizeof(char *));
	while (tab[++i])
		new[i] = ft_strdup(tab[i]);
	new[i] = ft_strdup(str);
	return (new);
}
