/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstdelone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:51:33 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 10:07:37 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_dlstdelone(t_dlist **lst)
{
	t_dlist const	*tmp = *lst;

	if (!(*lst))
		return ;
	else if (!(*lst)->prev && (*lst)->next)
	{
		(*lst) = (*lst)->next;
		(*lst)->prev = NULL;
	}
	else if (!(*lst)->next && !(*lst)->prev)
		(*lst) = NULL;
	else if (!(*lst)->next && (*lst)->prev)
		(*lst)->prev->next = NULL;
	else if ((*lst)->next && (*lst)->prev)
	{
		(*lst)->next->prev = (*lst)->prev;
		(*lst)->prev->next = (*lst)->next;
	}
	free((void *)tmp);
}
