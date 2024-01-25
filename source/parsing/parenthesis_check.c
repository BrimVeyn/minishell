/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:38:07 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 13:38:24 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	parenthesis_check(char *input)
{
	int p;
	int	i;
	
	i = 0;
	p = 0;
	while (input[i])
	{
		p += (input[i] == '(');
		p -= (input[i] == ')');
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
