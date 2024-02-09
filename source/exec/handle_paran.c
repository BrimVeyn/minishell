/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paran.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:09:49 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/09 12:05:36 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_pc_paran(t_pipe *d_pipe)
{
	// printf("p: %d\n", d_pipe->p_cpt);
	if (d_pipe->failed == 1)
		d_pipe->p_return = 0;
	else
		d_pipe->p_return = 1;
	d_pipe->p_nbr--;
	d_pipe->p_cpt--;
	d_pipe->p_trig = 1;
}

void	p_parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i][0] == P_O)
		d_pipe->p_cpt++;
	else if (d_token->type[*i][0] == P_C)
		handle_pc_paran(d_pipe);
	else if (d_token->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0)
		handle_cmd(d_token, d_pipe, denv, i);
}

void	p_while(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	(*i)++;
	while (d_pipe->p_nbr > 0)
	{
		p_parse_type(d_token, d_pipe, denv, i);
		if (d_pipe->p_trig == 0)
			(*i)++;
		else
			d_pipe->p_trig = 0;
	}
	dup2(d_pipe->old_stdout, STDOUT_FILENO);
}
