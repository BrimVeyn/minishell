/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:10:04 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:48 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// REMOVE WRONG DES OPES, bug possible

int	next_ope(t_tok *tdata, int i)
{
	i++;
	while (i < tdata->t_size)
	{
		if (tdata->type[i][0] == AND)
			return (AND);
		if (tdata->type[i][0] == PIPE)
			return (PIPE);
		else if (tdata->type[i][0] == OR)
			return (OR);
		i++;
	}
	return (-42);
}

int	previous_ope(t_tok *tdata, int i)
{
	i--;
	while (i >= 0)
	{
		if (tdata->type[i][0] == AND)
			return (AND);
		else if (tdata->type[i][0] == PIPE)
			return (PIPE);
		else if (tdata->type[i][0] == OR)
			return (OR);
		i--;
	}
	return (-42);
}
