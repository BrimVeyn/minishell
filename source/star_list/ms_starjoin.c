/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:26:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/16 15:44:05 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// char *ms_starjoin(t_dlist **slist, char *word)
// {
// 	t_dlist *current;
// 	char *new;
//
// 	current = *slist;
// 	new = ft_strdup("");
// 	while (current != NULL)
// 	{
// 		new = ft_strjoin_free(new, ft_strdup(current->str));
// 		new = ft_strjoin(new, " ");
// 		// ft_printf("NEW = %fs || CURRENT = %fs\n", new, current->str);
// 		current = current->next;
// 	}
// 	free(word);
// 	return (new);
// }

char *ms_starjoin(t_dlist **slist, char *word)
{
	(void) word;
    if (!slist || !*slist) return NULL;

    t_dlist *current = *slist;
    char *new = ft_strdup("");
    char *temp;

    while (current != NULL) {
        temp = ft_strjoin(new, current->str);
        free(new);
        new = temp;
        if (current->next != NULL) {
            temp = ft_strjoin(new, " ");
            free(new);
            new = temp;
        }
        current = current->next;
    }

    return new;
}
