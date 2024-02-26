/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:30 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/26 10:00:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



void	b_redi(t_tok *tdata, t_pipe *d_pipe, int i)
{
	if (access(tdata->tokens[i + 1][0], F_OK | R_OK) == 0)
		perror("minishell:");
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->input = open(tdata->tokens[i + 1][0], O_RDONLY);
}

void	b_redi_out(t_tok *tdata, t_pipe *d_pipe, int i)
{
	if (access(tdata->tokens[i + 1][0], F_OK | W_OK) == 0)
	{
		perror("Minishell:");
		return ;
	}
	if (d_pipe->output != -1)
		close(d_pipe->output);
	if (tdata->type[i][0] == S_AR)
		d_pipe->output = open(tdata->tokens[i + 1][0],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		d_pipe->output = open(tdata->tokens[i + 1][0],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	free_exit(t_tok *tdata, t_pipe *d_pipe, t_env *denv)
{
	ms_reset_fd(d_pipe);
	ms_h_unlink(d_pipe);
	(void)d_pipe;
	(void)denv;
	(void)tdata;
}

void	b_parse_nf(t_tok *tdata, t_env *denv, int *i, t_pipe *d_pipe)
{
	if (!ft_strcmp(tdata->tokens[*i][0], "export"))
		b_export(tdata->tokens[*i], denv);
	if (!ft_strcmp(tdata->tokens[*i][0], "unset"))
		b_unset(tdata->tokens[*i], denv);
	if (!ft_strcmp(tdata->tokens[*i][0], "cd"))
		b_cd(tdata->tokens[*i], denv);
	if (!ft_strcmp(tdata->tokens[*i][0], "exit"))
	{
		b_exit(tdata->tokens[*i], d_pipe);
		free_exit(tdata, d_pipe, denv);
	}
}

void	b_parse(t_tok *tdata, t_env *denv, int *i)
{
	if (!ft_strcmp(tdata->tokens[*i][0], "echo"))
		b_echo(tdata, i);
	if (!ft_strcmp(tdata->tokens[*i][0], "env"))
		b_env(denv);
	if (!ft_strcmp(tdata->tokens[*i][0], "pwd"))
		b_pwd();
}
