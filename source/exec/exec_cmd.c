/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:49:59 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/25 16:30:00 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

void exec_id0(t_pipe *d_pipe, t_tok *d_token, int id, int *i)
{

	signal(SIGINT, SIG_IGN);
	waitpid(id, &exitno ,0);
	init_sig();
	d_pipe->failed = 0;
	if (exitno != 0)
		d_pipe->failed = 1;
	if (d_pipe->failed == 1 && *i < d_token->t_size)
	{
		if (d_token->type[*i + 1] != OR)
		{
			if (d_token->type[*i + 1] == P_C)
				if (d_pipe->p_cpt >= 0)
					d_pipe->p_return[d_pipe->p_cpt] = 1;
			d_pipe->or_return = 1;
			d_pipe->failed = 0;
		}
	}
	return;
}

void c_execve(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i] == BUILTIN)
	{
		ft_printf("gros con\n");
		handle_built(d_token, d_pipe, denv, i);
	}
	else
	{
		execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
	}
}

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int id;

	j = 0;
	id = fork();
	if (id != 0)
	{
		exec_id0(d_pipe, d_token, id, i);
		return;
	}
	while(d_token->tokens[*i][j])
	{
		if (d_token->type[*i] == D_AL)
		{
			heredoc(d_pipe, d_token, denv, i);
			d_token->tokens[*i][j + 1] = ft_sprintf("%fs%d", ".temp_heredoc", d_pipe->nbr_h);
		}
		j++;
	}
	close(d_pipe->old_stdin);
	close(d_pipe->old_stdout);
	c_execve(d_token, d_pipe, denv, i);
	perror("execve failed connard");
	exit(EXIT_FAILURE);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
}

