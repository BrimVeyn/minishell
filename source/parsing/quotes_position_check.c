/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_position_check.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:31:39 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 16:10:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_quotes_whitelist(int type)
{
	if (type == AND || type == OR || type == S_AL || type == S_AR ||
		type == D_AL || type == D_AR || type == PIPE)
		return (TRUE);
	return (ERROR);
}

int	quotes_position_check(t_tok *tdata)
{
	int	i;

	i = 0;
	while (tdata->tokens[i])
	{
		if ((tdata->type[i] == P_O && i != 0) && (i > 0 && ms_quotes_whitelist(tdata->type[i - 1]) == ERROR))
        {
			fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i + 1][0]);
			return (ERROR);
		}
		if ((tdata->type[i] == P_C && i != tdata->t_size - 1) && (i > 0 && ms_quotes_whitelist(tdata->type[i + 1]) == ERROR))
        {
			fd_printf(2, "minishell: syntax error near unexpected token `%fs'\n", tdata->tokens[i + 1][0]);
			return (ERROR);
        }
		i++;
	}
	return (TRUE);
}
