/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:12:28 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 12:14:18 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	check_redi(char ***tokens, int i)
{
	int	j;

	j = 0;
	while (tokens[i][j])
	{
		if (ft_strcmp("<", tokens[i][j]) == 0)
			return (1);
		j++;
	}
	return (0);
}

void	cmd_reset_fd(t_pipe *d_pipe)
{
	if (d_pipe->input != -1)
	{
		dup2(d_pipe->old_stdin, STDIN_FILENO);
		d_pipe->input = -1;
	}
	if (d_pipe->output != -1)
	{
		dup2(d_pipe->old_stdout, STDOUT_FILENO);
		d_pipe->output = -1;
	}
}

void	handle_cmd(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (*i < tdata->t_size)
	{
		if (cmd_redi(tdata, d_pipe, denv, i) == 1)
		{
			if (tdata->t_size > *i + 1 && tdata->type[*i + 1][0] == PIPE)
				exec_pipe(tdata, d_pipe, denv, i);
			return ;
		}
	}
	if ((tdata->t_size > *i + 1 && tdata->type[*i + 1][0] == PIPE)
		|| (*i > 0 && tdata->type[*i - 1][0] == PIPE))
	{
		w_exec_pipe(tdata, d_pipe, denv, i);
		d_pipe->t_r = 1;
	}
	// else if (tdata->type[*i][0] == WRONG && d_pipe->temp != AND && d_pipe->temp != OR)
	// {
	// 	// printf("HDFSDADA\n");
	// 	tdata->exitno = 127 << 8;
	// }
	else if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0
		&& d_pipe->or_return == 0 && tdata->type[*i][0] != WRONG && tdata->type[*i][0] != IGNORE)
	{
		exec_cmd(tdata, d_pipe, denv, i);
	}
	else if (tdata->type[*i][0] == WRONG && d_pipe->temp != OR
		&& d_pipe->temp != AND)
	{
		d_pipe->failed = 1;
		// printf("string: %s\ntype %d\n", tdata->tokens[*i][0], tdata->type[*i][0]);
		tdata->exitno = 127 << 8;
		cmd_reset_fd(d_pipe);
	}
}

void	cmd_pipe(t_tok *tdata, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (tdata->t_size > *i && tdata->type[*i + 1][0] == PIPE)
	{
		w_exec_pipe(tdata, d_pipe, denv, i);
		return ;
	}
	else if (*i > 0 && tdata->type[*i - 1][0] == PIPE)
	{
		w_exec_pipe(tdata, d_pipe, denv, i);
		return ;
	}
}
