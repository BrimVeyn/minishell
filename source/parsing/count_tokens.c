/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:36:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 15:36:32 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int count_tokens_helper(int *x, char *input, t_tokvar *tokvar)
{
	x[COUNTER] += 1;
	if (start_check(input, *tokvar, x[I]) == ERROR)
		return (ERROR);
	if (end_check(input, *tokvar, x[I]) == ERROR)
		return (ERROR);
	x[I] += tokvar->len;
	return (TRUE);
}

int count_tokens_helper2(int *x, char *input, t_tokvar *tokvar)
{
	if (tokvar->type == S_AL)
		x[DCOUNTER] = delimiter_check(&input[x[I] + 1]);
	else if (tokvar->type == D_AL)
		x[DCOUNTER] = delimiter_check(&input[x[I] + 2]);
	x[I] += 2 + x[DCOUNTER];
	if (x[DCOUNTER] == 0)
		return (ERROR);
	x[COUNTER] += 2;
	return (TRUE);
}

void count_tokens_helper3(int *x, char *input)
{
	x[I] += 2;
	while (input[x[I]] && !ms_isws(input[x[I]]))
		x[I]++;
	while (input[x[I]] && ms_tiktok(&input[x[I]]).type == CMD)
		x[I]++;
}

int count_tokens_helper4(int *x, char *input)
{
	t_tokvar tokvar;

	x[TRI] = 0;
	tokvar = ms_tiktok(&input[x[I]]);
	if (input[x[I]] && tokvar.type != CMD && tokvar.type != D_AL && tokvar.type != S_AL)
		if (count_tokens_helper(x, input, &tokvar) == ERROR)
			return (ERROR);
	if (input[x[I]] && (tokvar.type == D_AL || tokvar.type == S_AL))
		if (count_tokens_helper(x, input, &tokvar) == ERROR)
			return (ERROR);
	while(input[x[I]] && ms_isws(input[x[I]]))
		x[I]++;
	while (input[x[I]] && ms_tiktok(&input[x[I]]).type == CMD)
	{
		x[TRI] = 1;
		x[I]++;
	}
	if (x[TRI] == 1)
		x[COUNTER] += 1;
	while (input[x[I]] && (ms_tiktok(&input[x[I]]).type == D_AL || ms_tiktok(&input[x[I]]).type == S_AL))
		count_tokens_helper3(x, input);
	return (TRUE);
}

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
