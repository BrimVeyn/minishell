/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:35:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 13:35:34 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int end_check(char *input, t_tokvar tokvar, int i)
{
	int	icpy;

	(void) tokvar;
	icpy = i + ms_tiktok(&input[i]).len;
	while (input[icpy] && ms_isws(input[icpy]))
		icpy++;
	if (!input[icpy] && ms_tiktok(&input[icpy - 2]).type != CMD)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[icpy - 2]).str);
		return (ERROR);
    }
	else if (!input[icpy] && ms_tiktok(&input[icpy - 1]).type != CMD && ms_tiktok(&input[icpy - 1]).type != P_O && ms_tiktok(&input[icpy - 1]).type != P_C)
    {
		fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", ms_tiktok(&input[icpy - 1]).str);
		return (ERROR);
    }
	return (0);	
}
