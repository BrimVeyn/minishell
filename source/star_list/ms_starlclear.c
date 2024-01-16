/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starlclear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:07:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/16 10:34:01 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_starclear(t_starlist **head)
{
	t_starlist *tmp;

	while (*head)
	{
		free((*head)->str);
		tmp = (*head)->next;
		free(*head);
		*head = tmp;
	}
}
