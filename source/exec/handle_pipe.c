/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:38:01 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/09 12:20:27 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	end_ep(t_pipe *d_pipe, t_env *denv, t_tok *d_token)
{
	if (d_pipe->b_pipefd[1] > -1)
		close(d_pipe->b_pipefd[1]);
	free_tpe(d_token, d_pipe, denv);
	exit(EXIT_SUCCESS);
}

void	exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
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
		if (previous_ope(d_token, *i) != PIPE)
			dup2(d_pipe->input, STDIN_FILENO);
		if (next_ope(d_token, *i) == PIPE
			&& d_pipe->output == d_pipe->old_stdout)
			dup2(d_pipe->pipefd[1], STDOUT_FILENO);
		else
			dup2(d_pipe->output, STDOUT_FILENO);
		close(d_pipe->pipefd[1]);
		close(d_pipe->output);
		if (d_pipe->t_f_redi == 0)
			c_execve(d_token, d_pipe, denv, i);
		end_ep(d_pipe, denv, d_token);
	}
}

void	cmd_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_pipe->output == -1)
		d_pipe->output = d_pipe->old_stdout;
	if (d_pipe->input == -1)
		d_pipe->input = d_pipe->old_stdin;
	exec_pipe(d_token, d_pipe, denv, i);
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

void	handle_cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (*i < d_token->t_size)
		cmd_redi(d_token, d_pipe, denv, i);
	if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
		cmd_exec_pipe(d_token, d_pipe, denv, i);
}

void	pipe_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i][0] == P_O && d_pipe->t_r == 0)
		handle_po(d_token, d_pipe, denv, i);
	else if (d_token->type[*i][0] == P_C && d_pipe->t_r == 0)
		handle_pc(d_pipe);
	else if (d_token->type[*i][0] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i][0] == OR)
		handle_or(d_pipe);
	else if (d_pipe->skip_and == 0 && d_token->type[*i][0] != PIPE)
		handle_cmd_pipe(d_token, d_pipe, denv, i);
}
