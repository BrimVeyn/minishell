/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:11:19 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 10:00:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	handle_po(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	d_pipe->p_nbr++;
	p_while(tdata, d_pipe, denv, i);
}

void	handle_pc(t_pipe *d_pipe)
{
	(void)d_pipe;
}

void	handle_wrong(t_pipe *d_pipe)
{
	d_pipe->failed = 1;
}

void	handle_and(t_pipe *d_pipe)
{
	if (d_pipe->p_nbr == 0)
		d_pipe->skip_or = 0;
	if (d_pipe->failed == 1 || d_pipe->p_return == 0)
	{
		d_pipe->skip_and = 1;
		d_pipe->failed = 0;
	}
	d_pipe->p_return = -1;
}

void	handle_or(t_pipe *d_pipe)
{
	d_pipe->skip_and = 0;
	if (d_pipe->p_nbr == 0)
	{
		d_pipe->p_return = -1;
	}
	if (d_pipe->failed == 0 || d_pipe->p_return == 1)
	{
		d_pipe->skip_or = 1;
	}
}
