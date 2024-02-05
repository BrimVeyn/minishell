/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/05 13:26:30 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>
#include <unistd.h>

extern int	g_exitno;

void	exec_id0(t_pipe *d_pipe, t_tok *d_token, int id, int *i)
{
	char	*buffer;

	buffer = malloc(2);
	signal(SIGINT, SIG_IGN);
	waitpid(id, &g_exitno, 0);
	init_sig();
	d_pipe->failed = 0;
	if (g_exitno != 0)
		d_pipe->failed = 1;
	if (d_pipe->failed == 1 && *i < d_token->t_size)
	{
		if (d_token->type[*i + 1][0] != OR)
		{
			if (d_token->type[*i + 1][0] == P_C)
				if (d_pipe->p_cpt >= 0)
					d_pipe->p_return[d_pipe->p_cpt] = 1;
			d_pipe->or_return = 1;
			d_pipe->failed = 0;
		}
	}
	free(buffer);
	return ;
}

void	c_execve(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	signal(SIGQUIT, SIG_DFL);
	if (d_token->type[*i][0] == BUILTIN)
	{
		handle_built(d_token, d_pipe, denv, i);
		if (d_pipe->b_pipefd[1] > -1)
			close(d_pipe->b_pipefd[1]);
		free_tpe(d_token, d_pipe, denv);
		exit(g_exitno);
	}
	else
	{
		if (d_pipe->b_pipefd[1] > -1)
			close(d_pipe->b_pipefd[1]);
		execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
		perror("execve failed");
		exit(g_exitno);
	}
}

void	handle_signs(t_pipe *d_pipe, t_tok *d_token, int *i)
{
	if (g_exitno != 0)
		d_pipe->failed = 1;
	if (d_pipe->failed == 1 && *i < d_token->t_size)
	{
		if (d_token->type[*i + 1][0] != OR)
		{
			if (d_token->type[*i + 1][0] == P_C)
				if (d_pipe->p_cpt >= 0)
					d_pipe->p_return[d_pipe->p_cpt] = 1;
			d_pipe->or_return = 1;
			d_pipe->failed = 0;
		}
	}
}

int	check_nf(t_tok *dt, t_pipe *dp, t_env *dv, int *i)
{
	if (ft_strcmp(dt->tokens[*i][0], "cd") == 0 || ft_strcmp(dt->tokens[*i][0],
			"export") == 0 || ft_strcmp(dt->tokens[*i][0], "exit") == 0
		|| ft_strcmp(dt->tokens[*i][0], "unset") == 0)
	{
		b_parse_nf(dt, dv, i, dp);
		handle_signs(dp, dt, i);
		return (1);
	}
	return (0);
}

void	exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	j;
	int	id;

	j = 0;
	if (check_nf(d_token, d_pipe, denv, i) == 1)
		return ;
	id = fork();
	if (id != 0)
	{
		exec_id0(d_pipe, d_token, id, i);
		return ;
	}
	close(d_pipe->old_stdin);
	close(d_pipe->old_stdout);
	c_execve(d_token, d_pipe, denv, i);
}
