/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 10:36:37 by nbardavi          #+#    #+#             */
/*   Updated: 2024/02/08 16:17:51 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

extern int	g_exitno;

void	r_parse_error(t_pipe *d_pipe)
{
	if (d_pipe->failure == D_AR || d_pipe->failure == S_AR)
	{
		d_pipe->output = -1;
		d_pipe->redi = 0;
		dup2(d_pipe->old_stdout, STDOUT_FILENO);
		fd_printf(2, "minishell: %fs: %fs\n", d_pipe->file_name,
			strerror(errno));
	}
	if (d_pipe->failure == S_AL)
	{
		d_pipe->redi = 0;
		d_pipe->t_cat = 1;
		close(STDIN_FILENO);
		// d_pipe->input = open("/dev/null", O_RDONLY);
		fd_printf(2, "minishell: %fs: %fs\n", d_pipe->file_name,
			strerror(errno));
	}
	g_exitno = 1 << 8;
	// exit (g_exitno);
}
