/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:38:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 13:39:31 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parenthesis_check(char *input)
{
	int	p;
	int q[2];
	int	i;

	i = 0;
	p = 0;
	q[0] = 0;
	q[1] = 0;
	while (input[i])
	{
		q[0] ^= (input[i] == '"');
		q[1] ^= (input[i] == '\'');
		p += (input[i] == '(' && !q[1] && !q[0]);
		p -= (input[i] == ')' && !q[1] && !q[0]);
		i++;
		if (p < 0)
		{
			fd_printf(2, "minishell: syntax error near unexpected token `)'\n");
			return (ERROR);
		}
	}
	if (p == 0)
		return (1);
	else
	{
		fd_printf(2, "minishell: syntax error near unexpected token `('\n");
		return (ERROR);
	}
}
