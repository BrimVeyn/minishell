/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:32:04 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 11:38:43 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ms_dlstjoin(t_dlist **dlist)
{
	t_dlist	*current;
	char	*new;
	char	*temp;

	if (!dlist || !*dlist)
		return (NULL);
	current = *dlist;
	new = ft_strdup("");
	while (current != NULL)
	{
		temp = ft_strjoin(new, current->str);
		free(new);
		new = temp;
		if (current->next != NULL)
		{
			temp = ft_strjoin(new, " ");
			free(new);
			new = temp;
		}
		current = current->next;
	}
	return (new);
}
