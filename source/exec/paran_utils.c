/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paran_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:04:03 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/25 13:12:05 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void p_count(t_tok *d_token, t_pipe *d_pipe)
{
	int i;

	i = 0;
	while(i < d_token->t_size)
	{
		if (d_token->type[i] == P_O)
			d_pipe->p_nbr++;
		i++;
	}
	d_pipe->p_return = ft_calloc(d_pipe->p_nbr, sizeof(int));
}
