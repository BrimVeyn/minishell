/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:36:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 16:16:01 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens_helper4(int *x, char *input)
{
	t_tokvar	tokvar;
	int			quotes[2];

	x[TRI] = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	tokvar = ms_tiktok(&input[x[I]]);
	if (input[x[I]] && tokvar.type != CMD && tokvar.type != D_AL
		&& tokvar.type != S_AL)
		if (count_tokens_helper(x, input, &tokvar) == ERROR)
			return (ERROR);
	if (input[x[I]] && (tokvar.type == D_AL || tokvar.type == S_AL))
		if (count_tokens_helper2(x, input, &tokvar) == ERROR)
			return (ERROR);
	while (input[x[I]] && ms_isws(input[x[I]]))
		x[I]++;
	while ((input[x[I]] && ms_tiktok(&input[x[I]]).type == CMD) || (input[x[I]]
			&& (quotes[0] == TRUE || quotes[1] == TRUE)))
		count_tokens_helper5(x, quotes, input);
	if (x[TRI] == 1)
		x[COUNTER] += 1;
	count_tokens_helper6(x , input);
	return (TRUE);
}

int	count_tokens(char *input)
{
	int	x[4];

	x[I] = 0;
	x[COUNTER] = 0;
	x[TRI] = 0;
	x[DCOUNTER] = 0;
	if (parenthesis_check(input) == ERROR
		|| quotes_parity_check(input) == ERROR)
		return (ERROR);
	while (input[x[I]])
		if (count_tokens_helper4(x, input) == ERROR)
			return (ERROR);
	return (x[COUNTER]);
}
