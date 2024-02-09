/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:30 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 12:20:12 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i][0] == P_O && d_pipe->t_r == 0)
		handle_po(d_token, d_pipe, denv, i);
	else if (d_token->type[*i][0] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (d_token->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0)
		handle_cmd(d_token, d_pipe, denv, i);
}

extern int	g_exitno;

void	w_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;

	j = 0;
	dup2(d_pipe->input, STDIN_FILENO);
	while ((next_ope(d_token, *i) == PIPE || (previous_ope(d_token, *i) == PIPE
				&& next_ope(d_token, *i) != PIPE)
			|| d_token->type[*i][0] == PIPE) && d_token->t_size > *i)
	{
		pipe_parse(d_token, d_pipe, denv, i);
		if (d_token->type[*i][0] != PIPE)
			d_pipe->f_cpt++;
		(*i)++;
	}
	dup2(d_pipe->old_stdin, STDIN_FILENO);
	while (d_pipe->f_cpt >= j)
	{
		if (g_exitno == 256)
			waitpid(d_pipe->f_id[d_pipe->f_cpt], NULL, 0);
		else
			waitpid(d_pipe->f_id[d_pipe->f_cpt], &g_exitno, 0);
		j++;
	}
	d_pipe->p_trig = 1;
}
