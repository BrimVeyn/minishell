/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paran.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:09:49 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/05 12:08:51 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	handle_or(t_pipe *d_pipe)
// {
// 	if (d_pipe->failed == 0 || d_pipe->p_return == 1)
// 		d_pipe->skip_or = 1;
// }
//
// void	handle_and_para(t_pipe *d_pipe)
// {
// 	d_pipe->skip_or_p = 0;
// 	if (d_pipe->failed == 1 || d_pipe->p_return == 0)
// 	{
// 		d_pipe->p_return (= -1);
// 		d_pipe->skip_and = 1;
// 		d_pipe->failed = 0;
// 	}
// }

void	handle_pc_paran(t_pipe *d_pipe)
{
	if (d_pipe->failed == 1)
		d_pipe->p_return = 0;
	else
		d_pipe->p_return = 1;
	d_pipe->p_nbr--;
	d_pipe->p_cpt--;
	d_pipe->p_trig = 1;
}

void	p_parse_type(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0)
		ms_parse(tdata, denv, *i);
	if (tdata->type[*i][0] == P_O)
		d_pipe->p_cpt++;
	else if (tdata->type[*i][0] == P_C)
		handle_pc_paran(d_pipe);
	else if (tdata->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (tdata->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0)
		handle_cmd(tdata, d_pipe, denv, i);
}

void	p_while(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	(*i)++;
	while (d_pipe->p_nbr > 0)
	{
		if (*i == tdata->t_size)
			break;
		p_parse_type(tdata, d_pipe, denv, i);
		if (d_pipe->p_trig == 0)
			(*i)++;
		else
			d_pipe->p_trig = 0;
	}
	dup2(d_pipe->old_stdout, STDOUT_FILENO);
}
