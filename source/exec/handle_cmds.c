/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 10:12:28 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/06 14:47:41 by nbardavi         ###   ########.fr       */
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

void	handle_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (*i < d_token->t_size)
		if (cmd_redi(d_token, d_pipe, denv, i) == 1)
			return ;
	if ((d_token->t_size > *i + 1 && d_token->type[*i + 1][0] == PIPE) || (*i > 0 && d_token->type[*i - 1][0] == PIPE))
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		d_pipe->t_r = 1;
	}
	else if (d_pipe->skip_and == 0 && d_pipe->skip_or == 0
		&& d_pipe->or_return == 0 && d_token->type[*i][0] != WRONG)
		exec_cmd(d_token, d_pipe, denv, i);
	cmd_reset_fd(d_pipe);
}

void	cmd_pipe(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->t_size > *i && d_token->type[*i + 1][0] == PIPE)
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		return ;
	}
	else if (*i > 0 && d_token->type[*i - 1][0] == PIPE)
	{
		w_exec_pipe(d_token, d_pipe, denv, i);
		return ;
	}
}
