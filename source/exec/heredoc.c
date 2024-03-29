/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:59:09 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 16:50:04 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		tprint(char ***string);

void	end_heredoc(char *save, char *sasave, t_pipe *d_pipe, t_env *denv)
{
	ms_lst_b(&denv->history, ms_lst_new(ft_strdup(save)));
	reset_history(denv);
	fd_printf(d_pipe->heredoc, "%s", sasave);
	d_pipe->input = d_pipe->heredoc;
	add_history(save);
	free(save);
}

int	heredoc(t_pipe *d_pipe, t_tok *dt, t_env *denv, int *i)
{
	char	*f_name;
	char	*save;
	char	*limiter;
	char	*sasave;

	limiter = ft_strdup(dt->tokens[*i][check_here(dt->tokens, *i) + 1]);
	f_name = h_create_file(d_pipe);
	save = h_redo(d_pipe, dt, limiter);
	if (save == NULL)
		return (close(d_pipe->heredoc), free(limiter), free(f_name), D_AL);
	sasave = ft_strdup(save);
	if (d_pipe->h_trigger == 0)
		save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	else
	{
		free(save);
		save = ft_sprintf("%fs", ms_getlast(denv));
	}
	end_heredoc(save, sasave, d_pipe, denv);
	close(d_pipe->input);
	open(f_name, O_RDWR);
	free(f_name);
	return (free(limiter), 0);
}

extern int	g_signal;

void	t_heredoc(t_tok *tdata, int *i, char *limiter)
{
	char		*input;
	static int	cpt;

	cpt = 1;
	if (limiter == NULL)
		limiter = ft_strdup(tdata->tokens[*i + 1][0]);
	while (1)
	{
		input = readline("> ");
		if (input == NULL && g_signal != 2)
		{
			fd_printf(2, "minishell:");
			fd_printf(2, "warning: here-document at line %d", cpt);
			fd_printf(2, " delimited by end-of-file (wanted '%s')\n", limiter);
			return ;
		}
		else if (ft_strcmp(limiter, input) == 0)
			break ;
		cpt++;
	}
	free(limiter);
	tdata->exitno = 0;
}
