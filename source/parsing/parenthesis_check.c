/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:38:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 16:09:43 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parenthesis_check(char *input)
{
	int	q[4];

	if (ms_setint(&q[0], 0), ms_setint(&q[1], 0), ms_setint(&q[2], 0),
		ms_setint(&q[3], 0), input)
		(void)q[3];
	while (input[q[3]])
	{
		q[0] ^= (input[q[3]] == '"');
		q[1] ^= (input[q[3]] == '\'');
		q[2] += (input[q[3]] == '(' && !q[1] && !q[0]);
		q[2] -= (input[q[3]] == ')' && !q[1] && !q[0]);
		q[3]++;
		if (q[2] < 0)
		{
			fd_printf(2, "minishell: syntax error near unexpected token `)'\n");
			return (ERROR);
		}
	}
	if (q[2] == 0)
		return (1);
	else
	{
		fd_printf(2, "minishell: syntax error near unexpected token `('\n");
		return (ERROR);
	}
}
