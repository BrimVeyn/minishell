/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:38:01 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/30 21:49:35 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		if (next_ope(d_token, *i) == PIPE && d_pipe->output == d_pipe->old_stdout)
			dup2(d_pipe->pipefd[1], STDOUT_FILENO);
		else
			dup2(d_pipe->output, STDOUT_FILENO);
		close(d_pipe->pipefd[1]);
		close(d_pipe->output);
		c_execve(d_token, d_pipe, denv, i);
		perror("\nexecve failed");
		exit(EXIT_FAILURE);
	}
}

void	cmd_exec_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_pipe->output == -1)
		d_pipe->output = d_pipe->old_stdout;
	if (d_pipe->input == -1)
		d_pipe->input = d_pipe->old_stdin;
	// ft_printf("input:%d\noutput:%d\n", d_pipe->input, d_pipe->output);
	exec_pipe(d_token, d_pipe, denv, i);
	if (d_pipe->output == d_pipe->old_stdout)
		d_pipe->output = -1;
	if (d_pipe->input == d_pipe->old_stdin)
		d_pipe->input = -1;
	if (d_pipe->input != -1)
	{
		dup2(d_pipe->old_stdin, STDIN_FILENO && d_pipe->t_cat == 0);
		d_pipe->input = -1;
	}
	if (d_pipe->output != -1)
	{
		dup2(d_pipe->old_stdout, STDOUT_FILENO && d_pipe->t_cat == 0);
		d_pipe->output = -1;
	}
}

void	handle_cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (*i < d_token->t_size)
		if (cmd_redi(d_token, d_pipe, i, 0) == 1)
			return;
	// print_tokens(d_token);
	if (p_here > -1)
		cmd_here(d_token, d_pipe, denv, i);
	if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0 && d_pipe->or_return == 0)
		cmd_exec_pipe(d_token, d_pipe, denv, i);
}

void	pipe_parse(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	p_here;

	p_here = check_here(d_token->tokens, *i);
	if (d_token->type[*i] == D_AL)
		handle_d_al(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == S_AL)
		b_redi(d_token, d_pipe, *i);
	else if ((d_token->type[*i] == CMD && d_pipe->skip_and == 0)
		|| d_token->type[*i] == WRONG || d_token->type[*i] == BUILTIN)
		handle_cmd_pipe(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_O)
		handle_po(d_token, d_pipe, denv, i);
	else if (d_token->type[*i] == P_C)
		handle_pc(d_pipe);
	else if (d_token->type[*i] == AND)
		handle_and(d_pipe);
	else if (d_token->type[*i] == OR)
		handle_or(d_pipe);
}
