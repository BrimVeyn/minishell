/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:11:19 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/26 10:29:29 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

void	handle_po(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	d_pipe->p_cpt++;
	p_while(d_token, d_pipe, denv, i);
}

void	handle_pc(t_pipe *d_pipe)
{
	d_pipe->p_nbr--;
	d_pipe->p_cpt--;
}

void	handle_wrong(t_pipe *d_pipe)
{
	exitno = 127;
	d_pipe->failed = 1;
}

void	handle_and(t_pipe *d_pipe)
{
	d_pipe->skip_or = 0;
	if (d_pipe->failed == 1 || d_pipe->p_return == 0)
	{
		d_pipe->p_return[d_pipe->p_cpt] = -1;
		d_pipe->skip_and = 1;
		d_pipe->failed = 0;
	}
	// ft_printf("\n\n\nskip and : %d\n", d_pipe->skip_and);
}

void	handle_or(t_pipe *d_pipe)
{
	if (d_pipe->failed == 0 || d_pipe->p_return[d_pipe->p_cpt] == 1)
		d_pipe->skip_or = 1;
}
