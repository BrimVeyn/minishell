/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:26:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 13:28:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ms_starjoin(t_starlist **slist)
{
	t_starlist	*current;
	char		*new;
	char		*temp;

	if (!slist || !*slist)
		return (NULL);
	current = *slist;
	new = ft_strdup("");
	while (current != NULL)
	{
		temp = ft_strjoin(new, current->str);
		free(new);
		new = temp;
		current = current->next;
	}
	return (new);
}
