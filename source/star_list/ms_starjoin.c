/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:26:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/18 11:38:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *ms_starjoin(t_starlist **slist)
{
    if (!slist || !*slist) return NULL;

    t_starlist *current = *slist;
    char *new = ft_strdup("");
    char *temp;

    while (current != NULL) {
        temp = ft_strjoin(new, current->str);
        free(new);
        new = temp;
        current = current->next;
    }
    return new;
}
