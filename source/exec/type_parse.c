/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 09:26:32 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/24 15:08:05 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_d_al(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i + 2] == CMD && d_token->t_size > 2)
		ms_place_h(d_token, h_before(d_pipe, d_token, denv, i), *i);
	else
		t_heredoc(d_token, i, NULL);
			// besoin possible de sortir de la fonction parse_type
}

void	parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (d_token->type[*i] == BUILTIN)
		b_parse(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == D_AL)
		handle_d_al(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == S_AL)
		b_redi(d_token, d_pipe, *i);
	else if (d_token->type[*i] == CMD && d_pipe->skip_and == 0)
		handle_cmd(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_O && d_pipe->t_r == 0)
		handle_po(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (d_token->type[*i] == WRONG)
		handle_wrong(d_token, d_pipe);
	else if (d_token->type[*i] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i] == OR)
		handle_or(d_pipe);
}
