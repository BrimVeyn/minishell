/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:30 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/01 15:19:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	sigint_spe(int sig_num);

void	parse_type(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (tdata->type[*i][0] == P_O && d_pipe->t_r == 0)
		handle_po(tdata, d_pipe, denv, i);
	else if (tdata->type[*i][0] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (tdata->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (tdata->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0)
    {
		ms_parse(tdata, denv, *i);
		handle_cmd(tdata, d_pipe, denv, i);
    }
}



void	w_exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;

	j = 0;
	dup2(d_pipe->input, STDIN_FILENO);
	while ((next_ope(tdata, *i) == PIPE || (previous_ope(tdata, *i) == PIPE
				&& next_ope(tdata, *i) != PIPE)
			|| tdata->type[*i][0] == PIPE) && tdata->t_size > *i)
	{
		pipe_parse(tdata, d_pipe, denv, i);
		if (tdata->type[*i][0] != PIPE)
			d_pipe->f_cpt++;
		(*i)++;
	}
	dup2(d_pipe->old_stdin, STDIN_FILENO);
	while (d_pipe->f_cpt >= j)
	{
		signal(SIGINT, SIG_IGN);
		if (tdata->exitno == 256 || tdata->exitno == 127 * 256)
			waitpid(d_pipe->f_id[d_pipe->f_cpt], NULL, 0);
		else
			waitpid(d_pipe->f_id[d_pipe->f_cpt], &tdata->exitno, 0);
		signal(SIGINT, sigint_spe);
		j++;
	}
	d_pipe->p_trig = 1;
}
