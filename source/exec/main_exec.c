/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:28:00 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/02 11:23:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

void	ms_reset_fd(t_pipe d_pipe)
{
	dup2(d_pipe.old_stdout, STDOUT_FILENO);
	dup2(d_pipe.old_stdin, STDIN_FILENO);
}

static int	end_main(t_pipe d_pipe)
{
	ms_reset_fd(d_pipe);
	ms_h_unlink(&d_pipe);
	ms_free_pipe(&d_pipe);
	if (WIFEXITED(g_exitno))
		g_exitno = WEXITSTATUS(g_exitno);
	if (d_pipe.t_exit == 1)
		return (1);
	return (0);
}

int	ms_main_pipe(t_tok d_token, t_env *denv)
{
	int		i;
	t_pipe	d_pipe;

	i = 0;
	if (d_token.tokens == NULL)
		return (0);
	init_d_pipe(&d_pipe);
	p_count(&d_token, &d_pipe);
	while (i < d_token.t_size)
	{
		d_pipe.t_r = 0;
		if (d_token.type[0] == -1)
			break ;
		parse_type(&d_token, &d_pipe, denv, &i);
		i++;
		if (d_pipe.t_exit == 1)
			break ;
	}
	return (end_main(d_pipe));
}
