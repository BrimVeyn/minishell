/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 09:42:39 by nbardavi          #+#    #+#             */
/*   Updated: 2024/03/04 15:13:46 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <signal.h>

void	exec_id0_helper(t_pipe *d_pipe)
{
	d_pipe->or_return = 1;
	d_pipe->failed = 0;
}

void	handle_cmd_helper(t_tok *tdata, t_pipe *d_pipe)
{
	d_pipe->failed = 1;
	tdata->exitno = 127 << 8;
}

int	get_h_cpt(int trigger)
{
	static int	h_cpt;

	if (trigger == 1)
		h_cpt = 0;
	else if (trigger == 0)
		h_cpt++;
	return (h_cpt);
}
