/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:26:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 14:20:09 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ms_starjoin(t_starlist **slist)
{
	t_starlist	*current;
	char		*new;

	if (!slist || !*slist)
		return (NULL);
	current = *slist;
	new = ft_strdup("");
	while (current != NULL)
	{
		new = ft_strjoin_s2(current->str, new);
		current = current->next;
	}
	return (new);
}
