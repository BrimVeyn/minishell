/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlsort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:14:12 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 09:03:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_dlsort(t_dlist **flist)
{
	t_dlist		*current;
	int			i;
	int const	list_len = ms_dlstlen(flist);
	char		*cstrcpy;
	char		*nstrcpy;

	i = 0;
	while (i < list_len)
	{
		current = *flist;
		while (current->next)
		{
			cstrcpy = ms_strtolower(current->str);
			nstrcpy = ms_strtolower(current->next->str);
			if (ft_strcmp(cstrcpy, nstrcpy) > 0)
				ms_dswapstr(current, current->next);
			current = current->next;
			free(cstrcpy);
			free(nstrcpy);
		}
		i++;
	}
}
