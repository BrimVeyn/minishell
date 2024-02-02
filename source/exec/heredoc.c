/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:59:09 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/02 11:19:00 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	end_heredoc(char *save, char *sasave, t_pipe *d_pipe, t_env *denv)
{
	ms_lst_b(&denv->history, ms_lst_new(ft_strdup(save)));
	reset_history(denv);
	fd_printf(d_pipe->heredoc, "%s", sasave);
	add_history(save);
	free(save);
	close(d_pipe->heredoc);
}

char	*heredoc(t_pipe *d_pipe, t_tok *dt, t_env *denv, int *i)
{
	char	*save;
	char	*f_name;
	char	*limiter;
	char	*sasave;

	if (d_pipe->h_before == 1)
		limiter = ft_strdup(dt->tokens[*i][check_here(dt->tokens, *i) + 1]);
	else
		limiter = ft_strdup(dt->tokens[*i + 1][0]);
	f_name = h_create_file(d_pipe);
	cut_here(dt, i);
	save = h_redo(d_pipe, dt, limiter);
	if (save == NULL)
		return (close(d_pipe->heredoc), free(limiter), f_name);
	sasave = ft_strdup(save);
	if (d_pipe->h_trigger == 0)
		save = ft_sprintf("%fs\n%s%fs", ms_getlast(denv), save, limiter);
	else
		save = ft_sprintf("%fs", ms_getlast(denv));
	end_heredoc(save, sasave, d_pipe, denv);
	return (free(limiter), f_name);
}

extern int	g_exitno;

void	t_heredoc(t_tok *d_token, int *i, char *limiter)
{
	char	*input;
	int		cpt;

	cpt = 1;
	if (limiter == NULL)
		limiter = ft_strdup(d_token->tokens[*i + 1][0]);
	while (1)
	{
		input = readline("> ");
		if (input == NULL)
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
	g_exitno = 0;
}

char	*h_handle(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char	*temp;

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	temp = heredoc(d_pipe, d_token, denv, i);
	return (temp);
}
