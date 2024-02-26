/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 10:00:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>
#include <unistd.h>



void	sigint_spe(int sig_num);

void	exec_id0(t_pipe *d_pipe, t_tok *tdata, int id, int *i)
{
	char	*buffer;

	buffer = malloc(2);
	signal(SIGINT, SIG_IGN);
	waitpid(id, &tdata->exitno, 0);
	signal(SIGINT, sigint_spe);
	d_pipe->failed = 0;
	if (tdata->exitno != 0)
		d_pipe->failed = 1;
	if (d_pipe->failed == 1 && *i < tdata->t_size)
	{
		if (tdata->t_size > *i + 1 && tdata->type[*i + 1][0] != OR)
		{
			if (tdata->t_size > *i + 1 && tdata->type[*i + 1][0] == P_C)
				if (d_pipe->p_cpt >= 0)
					d_pipe->p_return = 1;
			d_pipe->or_return = 1;
			d_pipe->failed = 0;
		}
	}
	free(buffer);
	return ;
}

void	c_execve(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	signal(SIGQUIT, SIG_DFL);
	if (tdata->type[*i][0] == BUILTIN)
	{
		handle_built(tdata, d_pipe, denv, i);
		if (d_pipe->b_pipefd[1] > -1)
			close(d_pipe->b_pipefd[1]);
		free_tpe(tdata, d_pipe, denv);
		exit(tdata->exitno);
	}
	else
	{
		if (d_pipe->b_pipefd[1] > -1)
			close(d_pipe->b_pipefd[1]);
		execve(tdata->tokens[*i][0], tdata->tokens[*i], denv->f_env);
		exit(tdata->exitno);
	}
}

void	handle_signs(t_pipe *d_pipe, t_tok *tdata, int *i)
{
	if (tdata->exitno != 0)
		d_pipe->failed = 1;
	if (d_pipe->failed == 1 && *i < tdata->t_size)
	{
		if (tdata->t_size > *i + 1 && tdata->type[*i + 1][0] != OR)
		{
			if (tdata->t_size > *i + 1 && tdata->type[*i + 1][0] == P_C)
				if (d_pipe->p_cpt >= 0)
					d_pipe->p_return = 1;
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

void	exec_cmd(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	int	id;

	if (check_nf(tdata, d_pipe, denv, i) == 1)
		return ;
	id = fork();
	if (id != 0)
	{
		exec_id0(d_pipe, tdata, id, i);
		return ;
	}
	close(d_pipe->old_stdin);
	close(d_pipe->old_stdout);
	c_execve(tdata, d_pipe, denv, i);
}
