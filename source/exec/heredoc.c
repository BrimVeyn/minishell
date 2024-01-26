/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:59:09 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/26 14:21:19 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *heredoc(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char	*save;
	char	*f_name;
	char	*limiter;
	char	*sasave;

	if (d_pipe->h_before == 1)
		limiter = d_token->tokens[*i][check_here(d_token->tokens, *i) + 1];
	else
		limiter = d_token->tokens[*i + 1][0];
	f_name = h_create_file(d_pipe);
	cut_here(d_token, i);
	save = h_redo(d_pipe, d_token, limiter);
	sasave = ft_strdup(save);
	if (d_pipe->h_trigger == 0)
		save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	else
		save = ft_sprintf("%fs", ms_getlast(denv));
	ms_lst_b(&denv->history, ms_lst_new(ft_strdup(save)));
	reset_history(denv);
	fd_printf(d_pipe->heredoc, "%s", sasave);
	add_history(save);
	free(save);
	close(d_pipe->heredoc);
	return (f_name);
}

extern int g_exitno;

void t_heredoc(t_tok *d_token, int *i, char *limiter)
{
	char	*input;
	int		cpt;

	cpt = 1;
	if (limiter == NULL)
		limiter = d_token->tokens[*i + 1][0];
	while(1)
	{
		input = readline("> ");
		if (input == NULL)
		{
			printf("minishell: warning: here-document at line %d delimited by end-of-file (wanted '%s')\n", cpt, limiter);
			return;
		}
		else if (ft_strcmp(limiter, input) == 0)
			break;
		cpt++;
	}
	g_exitno = 0;
}

char *h_handle(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;

	return (heredoc(d_pipe, d_token, denv, i));	
}
