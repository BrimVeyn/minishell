/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:16:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/15 17:17:02 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_dprint(t_dlist **lst)
{
	t_dlist *current = *lst;
	int	i = 0;

	ft_printf("-------LIST-------\n");
	while(current)
	{
		printf("LST[%d] = %s\n", i++, current->str);
		current = current->next;
	}
	ft_printf("------------------\n");
}

t_dlist *ms_match_check(t_dlist *el)
{
	if (!ft_strncmp(el->str, "two", 3))
		el->i = ERROR;
	return (el);
}

t_dlist *ms_dlstmap(t_dlist **lst, t_dlist *(*f)(t_dlist *))
{
	t_dlist **current;
	t_dlist *newhead = NULL;
	t_dlist const *save = *lst;

	int	i = 0;
	current = lst;
	while(*current)
	{
		ms_dprint(current);
		(*current) = (f)((*current));
		if ((*current)->i != ERROR)
			ms_dlstab(&newhead, ms_dlstnew((*current)->str, (*current)->i)); 
		(*current) = (*current)->next;
	}
	ms_dlstclear((t_dlist **)&save);
	return (newhead);
}
