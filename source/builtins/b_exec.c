/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:33:30 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/09 09:58:55 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	b_redi(t_tok *d_token, t_pipe *d_pipe, int i)
{
	if (access(d_token->tokens[i + 1][0], F_OK | R_OK) == 0)
		perror("minishell:");
	if (d_pipe->input != -1)
		close(d_pipe->input);
	d_pipe->input = open(d_token->tokens[i + 1][0], O_RDONLY);
}

void	b_redi_out(t_tok *d_token, t_pipe *d_pipe, int i)
{
	if (access(d_token->tokens[i + 1][0], F_OK | W_OK) == 0)
	{
		perror("Minishell:");
		return ;
	}
	if (d_pipe->output != -1)
		close(d_pipe->output);
	if (d_token->type[i][0] == S_AR) // ATTENTION
		d_pipe->output = open(d_token->tokens[i + 1][0],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		d_pipe->output = open(d_token->tokens[i + 1][0],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	free_exit(t_tok *d_token, t_pipe *d_pipe, t_env *denv)
{
	ms_reset_fd(d_pipe);
	ms_h_unlink(d_pipe);
	(void)d_pipe;
	(void)denv;
	(void)d_token;
}

void	b_parse_nf(t_tok *d_token, t_env *denv, int *i, t_pipe *d_pipe)
{
	if (!ft_strcmp(d_token->tokens[*i][0], "export"))
		b_export(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "unset"))
		b_unset(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "cd"))
		b_cd(d_token->tokens[*i], denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "exit"))
	{
		b_exit(d_token->tokens[*i], d_pipe);
		free_exit(d_token, d_pipe, denv);
	}
}

void	b_parse(t_tok *d_token, t_env *denv, int *i)
{
	if (!ft_strcmp(d_token->tokens[*i][0], "echo"))
		b_echo(d_token, i);
	if (!ft_strcmp(d_token->tokens[*i][0], "env"))
		b_env(denv);
	if (!ft_strcmp(d_token->tokens[*i][0], "pwd"))
		b_pwd();
	if (!ft_strcmp(d_token->tokens[*i][0], "robin"))
		b_robin();
}

void	handle_built(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	(void)d_pipe;
	b_parse(d_token, denv, i);
}
