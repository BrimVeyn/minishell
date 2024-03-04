/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:00 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 10:51:47 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_reset_fd(t_pipe *d_pipe)
{
	dup2(d_pipe->old_stdout, STDOUT_FILENO);
	dup2(d_pipe->old_stdin, STDIN_FILENO);
}

extern int g_signal;

static int	end_main(t_pipe d_pipe, t_tok *tdata)
{
	ms_reset_fd(&d_pipe);
	ms_h_unlink(&d_pipe);
	ms_free_pipe(&d_pipe);
	tdata->exitno = WEXITSTATUS(tdata->exitno);
	if (d_pipe.t_exit == 1)
		return (1);
	return (0);
}

int	ms_main_pipe(t_tok *tdata, t_env *denv)
{
	int		i;
	t_pipe	d_pipe;

	i = 0;
	if (tdata->tokens == NULL)
		return (0);
	init_d_pipe(&d_pipe);
	p_count(tdata, &d_pipe);
	while (i < tdata->t_size)
	{
		d_pipe.t_r = 0;
		if (tdata->type[0][0] == -1)
			break ;
		parse_type(tdata, &d_pipe, denv, &i);
		i++;
		if (d_pipe.t_exit == 1)
			break ;
	}
	init_sig();
	return (end_main(d_pipe, tdata));
}
