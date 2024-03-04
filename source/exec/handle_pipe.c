/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:38:01 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 12:02:04 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	end_ep(t_pipe *d_pipe, t_env *denv, t_tok *tdata)
{
	if (d_pipe->b_pipefd[1] > -1)
		close(d_pipe->b_pipefd[1]);
	free_tpe(tdata, d_pipe, denv);
	exit(EXIT_SUCCESS);
}

void	exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	pipe(d_pipe->pipefd);
	d_pipe->f_id[d_pipe->f_cpt] = fork();
	if (d_pipe->f_id[d_pipe->f_cpt] > 0)
	{
		close(d_pipe->pipefd[1]);
		dup2(d_pipe->pipefd[0], STDIN_FILENO);
		close(d_pipe->pipefd[0]);
	}
	else if (d_pipe->f_id[d_pipe->f_cpt] == 0)
	{
		close(d_pipe->pipefd[0]);
		close(d_pipe->input);
		if (previous_ope(tdata, *i) != PIPE)
			dup2(d_pipe->input, STDIN_FILENO);
		if (next_ope(tdata, *i) == PIPE && d_pipe->output == d_pipe->old_stdout)
			dup2(d_pipe->pipefd[1], STDOUT_FILENO);
		else
			dup2(d_pipe->output, STDOUT_FILENO);
		close(d_pipe->pipefd[1]);
		close(d_pipe->output);
		if (d_pipe->t_f_redi == 0)
			c_execve(tdata, d_pipe, denv, i);
		end_ep(d_pipe, denv, tdata);
	}
}

void	cmd_exec_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_pipe->output == -1)
		d_pipe->output = d_pipe->old_stdout;
	if (d_pipe->input == -1)
		d_pipe->input = d_pipe->old_stdin;
	exec_pipe(tdata, d_pipe, denv, i);
	if (d_pipe->output == d_pipe->old_stdout)
		d_pipe->output = -1;
	if (d_pipe->input == d_pipe->old_stdin)
		d_pipe->input = -1;
	if (d_pipe->input != -1)
	{
		if (d_pipe->redi == 0)
			dup2(d_pipe->old_stdin, STDIN_FILENO);
		else
			d_pipe->redi = 0;
		d_pipe->input = -1;
	}
	if (d_pipe->output != -1)
	{
		if (d_pipe->redi_o == 0)
			dup2(d_pipe->old_stdout, STDOUT_FILENO);
		else
			d_pipe->redi_o = 0;
		d_pipe->output = -1;
	}
}

void	handle_cmd_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (*i < tdata->t_size)
		cmd_redi(tdata, d_pipe, denv, i);
	if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
		cmd_exec_pipe(tdata, d_pipe, denv, i);
}

void	pipe_parse(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (tdata->type[*i][0] == P_O && d_pipe->t_r == 0)
		handle_po(tdata, d_pipe, denv, i);
	else if (tdata->type[*i][0] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (tdata->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (tdata->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0 && tdata->type[*i][0] != PIPE)
	{
		ms_parse(tdata, denv, *i);
		handle_cmd_pipe(tdata, d_pipe, denv, i);
	}
	if (tdata->type[*i][0] == WRONG && next_ope(tdata, *i) != PIPE)
	{
		printf("Hello\n");
		tdata->exitno = 127 << 8;
	}
}
