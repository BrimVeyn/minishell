/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_dlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:11:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/15 14:18:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_dlist	*ms_dlstnew(void *str, int i)
{
	t_dlist	*new;

	new = (t_dlist *) ft_calloc(1, sizeof(t_dlist));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->i = i;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
