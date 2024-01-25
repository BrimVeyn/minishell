/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_joinstarstar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:40:28 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 13:40:37 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char **ms_joinstarstar(char **p1, char **p2)
{
	char **new;
	int i;
	int	j;

	i = -1;
	j = -1;
	new = ft_calloc(ms_tablen(p1) + ms_tablen(p2) + 1, sizeof(char *));
	if (!new)
		return (NULL);
	while(p1[++i])
		new[i] = ft_strdup(p1[i]);
	while(p2[++j])
		new[i++] = ft_strdup(p2[j]);
	return(new);
}
