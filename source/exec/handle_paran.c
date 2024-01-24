/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paran.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 14:09:49 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/24 15:29:56 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void handle_pc_paran(t_pipe *d_pipe)
{
	if (d_pipe->or_return == 1)
		d_pipe->p_return[d_pipe->p_cpt] = 1;
	d_pipe->p_nbr--;
	d_pipe->p_cpt--;
}

void p_parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (d_token->type[*i] == P_O)
		d_pipe->p_cpt++;
	else if (d_token->type[*i] == P_C)
		handle_pc_paran(d_pipe);
	else if (d_token->type[*i] == BUILTIN)
		b_parse(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == D_AL)
		handle_d_al(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == S_AL)
		b_redi(d_token, d_pipe, *i);
	else if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
		handle_cmd(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == WRONG)
		handle_wrong(d_token, d_pipe);
	else if (d_token->type[*i] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i] == OR)
		handle_or(d_pipe);
	// ft_printf("Hello");
}

void p_redi(t_tok *d_token, t_pipe *d_pipe, int *i)
{
	int j;

	j = 0;
	while (d_token->type[*i + j] != P_C)
		j++;
	if (d_token->type[*i + j + 1] == S_AR)
	{
		d_pipe->p_redi_fd = open(d_token->tokens[*i + 2 +j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(d_pipe->p_redi_fd, STDOUT_FILENO);
	}
	else
		d_pipe->p_redi_fd = d_pipe->old_stdout;
	if (d_token->type[*i + j + 1] == S_AL)
	{
		d_pipe->input = open(d_token->tokens[*i + 2 + j][0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(d_pipe->input, STDIN_FILENO);
	}
}


void p_while(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	(*i)++;
	p_redi(d_token, d_pipe, i);
	while(d_pipe->p_nbr > 0)
	{
		p_parse_type(d_token, d_pipe, denv, i);
		if (d_pipe->p_trig == 0)
			(*i)++;
		else
			d_pipe->p_trig = 0;
	}
	dup2(d_pipe->old_stdout, STDOUT_FILENO);
}
