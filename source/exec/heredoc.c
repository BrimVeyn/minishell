/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 08:59:09 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/01 18:16:38 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*heredoc(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char	*save;
	char	*f_name;
	char	*limiter;
	char	*sasave;

	if (d_pipe->h_before == 1)
		limiter = ft_strdup(d_token->tokens[*i][check_here(d_token->tokens, *i) + 1]);
	else
		limiter = ft_strdup(d_token->tokens[*i + 1][0]);
	f_name = h_create_file(d_pipe);
	cut_here(d_token, i);
	save = h_redo(d_pipe, d_token, limiter);
	printf("heredoc: f_name: %s\n", f_name);
	if (save == NULL)
		return (close(d_pipe->heredoc), free(limiter), f_name);
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
	return (free(limiter), f_name);
}

extern int	g_exitno;

void	t_heredoc(t_tok *d_token, int *i, char *limiter)
{
	char	*input;
	int		cpt;

	cpt = 1;
	if (limiter == NULL)
		limiter = d_token->tokens[*i + 1][0];
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
	g_exitno = 0;
}

char	*h_handle(t_pipe *d_pipe, t_tok *d_token, t_env *denv, int *i)
{
	char *temp;

	d_pipe->h_trigger = 0;
	d_pipe->h_cpt = 0;
	temp = heredoc(d_pipe, d_token, denv, i);
	printf("h_handle: f_name :%s\n", temp);
	return (temp);
}
