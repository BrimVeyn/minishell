/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:02:14 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 12:02:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_dlstlen(t_dlist **flist)
{
	t_dlist	*current;
	int		i;

	current = *flist;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}
