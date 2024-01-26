/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starlnew.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:11:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/16 15:11:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_starlist	*ms_starlnew(void *str, int i)
{
	t_starlist	*new;

	new = (t_starlist *)ft_calloc(2, sizeof(t_starlist));
	if (new == NULL)
		return (NULL);
	new->str = str;
	new->type = i;
	new->next = NULL;
	return (new);
}
