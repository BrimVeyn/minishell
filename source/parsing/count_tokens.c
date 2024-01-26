/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:36:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 08:52:41 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_tokens(char *input)
{
	int x[4];

	x[I] = 0;
	x[COUNTER] = 0;
	x[TRI] = 0;
	x[DCOUNTER] = 0;
	if (parenthesis_check(input) == ERROR || quotes_parity_check(input) == ERROR)
		return (ERROR);
	while (input[x[I]])
		if (count_tokens_helper4(x, input) == ERROR)
			return (ERROR);
	return (x[COUNTER]);
}
