/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paran_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:04:03 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 09:57:48 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	p_count(t_tok *tdata, t_pipe *d_pipe)
{
	int	i;

	i = 0;
	while (i < tdata->t_size)
	{
		if (tdata->type[i][0] == P_O)
			d_pipe->p_nbr++;
		i++;
	}
}
