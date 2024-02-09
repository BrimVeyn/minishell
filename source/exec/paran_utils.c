/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paran_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 09:30:35 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 09:30:36 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	p_count(t_tok *d_token, t_pipe *d_pipe)
{
	int	i;

	i = 0;
	while (i < d_token->t_size)
	{
		if (d_token->type[i][0] == P_O)
			d_pipe->p_nbr++;
		i++;
	}
	d_pipe->p_return = ft_calloc(d_pipe->p_nbr, sizeof(int));
}
