/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 14:41:53 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:42:13 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_exitno;

void exec_id0(t_pipe *d_pipe, t_tok *d_token, int id, int *i)
{
	char *buffer;

	buffer = malloc(2);
	close(d_pipe->b_pipefd[1]);
	signal(SIGINT, SIG_IGN);
	waitpid(id, &g_exitno ,0);
	init_sig();
	d_pipe->failed = 0;
	if (g_exitno != 0)
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
	if (d_token->type[*i] == BUILTIN && read(d_pipe->b_pipefd[0], buffer, 1) == 1)
		d_pipe->t_exit = 1;
	free(buffer);
	close(d_pipe->b_pipefd[0]);
	return;
}

void c_execve(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	if (d_token->type[*i] == BUILTIN)
	{
		handle_built(d_token, d_pipe, denv, i);
		close(d_pipe->b_pipefd[1]);
		free_tpe(d_token, d_pipe, denv);
		exit(g_exitno);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
	}
	else
	{
		close(d_pipe->b_pipefd[1]);
		execve(d_token->tokens[*i][0], d_token->tokens[*i], denv->f_env);
		perror("execve failed");
		exit(g_exitno);//TEMPORAIRE -> LEAKS, FONCTION SPECIAL A FAIRE
	}
}

void exec_cmd(t_tok *d_token, t_pipe *d_pipe, t_env *denv, int *i)
{
	int j;
	int id;

	j = 0;
	pipe(d_pipe->b_pipefd);
	id = fork();
	if (id != 0)
	{
		exec_id0(d_pipe, d_token, id, i);
		return;
	}
	close(d_pipe->b_pipefd[0]);
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
}

