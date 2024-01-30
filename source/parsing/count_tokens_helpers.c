/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 08:50:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 12:43:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens_helper(int *x, char *input, t_tokvar *tokvar)
{
	x[COUNTER] += 1;
	if (start_check(input, *tokvar, x[I]) == ERROR)
		return (ERROR);
	if (end_check(input, x[I]) == ERROR)
		return (ERROR);
	x[I] += tokvar->len;
	return (TRUE);
}

int	count_tokens_helper2(int *x, char *input, t_tokvar *tokvar)
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

void	count_tokens_helper3(int *x, char *input)
{
	ft_printf("OH ENCULE\n");
	x[I] += 2;
	while (input[x[I]] && !ms_isws(input[x[I]]))
		x[I]++;
	while (input[x[I]] && ms_tiktok(&input[x[I]]).type == CMD)
		x[I]++;
}

void	count_tokens_helper5(int *x, int *quotes, char *input)
{
	quotes[0] ^= (input[x[I]] == DQUOTE);
	quotes[1] ^= (input[x[I]] == SQUOTE);
	x[TRI] = 1;
	x[I]++;
}

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
	while (input[x[I]] && (ms_tiktok(&input[x[I]]).type == D_AL
			|| ms_tiktok(&input[x[I]]).type == S_AL))
		count_tokens_helper3(x, input);
	return (TRUE);
}
