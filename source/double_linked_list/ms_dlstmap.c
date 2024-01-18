/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:16:31 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 11:29:42 by bvan-pae         ###   ########.fr       */
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
		printf("LST[%d] = %s || i = %d\n", i++, current->str, current->i);
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

t_dlist *ms_dlstmap(t_dlist **lst, char *word, void (*f)(t_dlist *, char *))
{
	t_dlist **current;
	t_dlist *newhead;
	t_dlist *save;

	save = *lst;
	current = lst;
	newhead = NULL;
	while(*current)
	{
		(f)((*current), word);
		if ((*current)->i != ERROR)
			ms_dlstab(&newhead, ms_dlstnew(ft_strdup((*current)->str), (*current)->i)); 
		(*current) = (*current)->next;
	}
	// ms_dprint(&save);
	ms_dlstclear(&save);
	return (newhead);
}
