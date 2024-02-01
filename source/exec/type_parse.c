/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:42 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 11:11:53 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_d_al(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->t_size > 2 && d_token->type[*i + 2] == CMD)
	{
		d_pipe->h_before = 2;
		ms_place_h(d_token, h_handle(d_pipe, d_token, denv, i), *i);
	}
	else
		t_heredoc(d_token, i, NULL);
}

void	parse_type(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (d_token->type[*i] == D_AL)
		handle_d_al(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == S_AL)
		b_redi(d_token, d_pipe, *i);
	else if ((d_token->type[*i] == CMD && d_pipe->skip_and == 0)
		|| (d_token->type[*i] == BUILTIN))
		handle_cmd(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_O && d_pipe->t_r == 0)
		handle_po(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (d_token->type[*i] == WRONG)
		handle_wrong(d_pipe);
	else if (d_token->type[*i] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i] == OR)
		handle_or(d_pipe);
}

extern int	g_exitno;

void	w_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;

	j = 0;
	d_pipe->f_cpt = 0;
	dup2(d_pipe->input, STDIN_FILENO);
	while ((next_ope(d_token, *i) == PIPE || (previous_ope(d_token, *i) == PIPE
				&& next_ope(d_token, *i) != PIPE) || d_token->type[*i] == PIPE)
		&& d_token->t_size > *i)
	{
		pipe_parse(d_token, d_pipe, denv, i);
		d_pipe->f_cpt++;
		(*i)++;
	}
	dup2(d_pipe->old_stdin, STDIN_FILENO);
	while (d_pipe->f_cpt >= j)
	{
		waitpid(d_pipe->f_id[d_pipe->f_cpt], &g_exitno, 0);
		j++;
	}
	d_pipe->p_trig = 1;
}

void	ms_reset_fd(t_pipe d_pipe)
{
	dup2(d_pipe.old_stdout, STDOUT_FILENO);
	dup2(d_pipe.old_stdin, STDIN_FILENO);
}

int	end_main(t_tok d_token, t_pipe d_pipe, t_env *denv)
{
	ms_reset_fd(d_pipe);
	ms_h_unlink(&d_pipe);
	// ms_free_env(denv);
	ms_free_pipe(&d_pipe);
	if (WIFEXITED(g_exitno))
		g_exitno = WEXITSTATUS(g_exitno);
	if (d_pipe.t_exit == 1)
		return (1);
	return (0);
}

int	ms_main_pipe(t_tok d_token, t_env *denv)
{
	int		i;
	t_pipe	d_pipe;

	i = 0;
	if (d_token.tokens == NULL)
		return (0);
	init_d_pipe(&d_pipe);
	p_count(&d_token, &d_pipe);
	print_tokens(&d_token);
	printf("nbr token:%d\n", d_token.t_size);
	while (i < d_token.t_size)
	{
		d_pipe.t_r = 0;
		if (d_token.type[0] == -1)
			break ;
		parse_type(&d_token, &d_pipe, denv, &i);
		i++;
		if (d_pipe.t_exit == 1)
			break ;
	}
	return (end_main(d_token, d_pipe, denv));
}
