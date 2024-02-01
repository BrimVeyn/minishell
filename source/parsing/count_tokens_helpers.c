/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:30:36 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/01 13:15:50 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_tokens_helper(int *x, char *input, t_tokvar *tokvar)
{
	x[COUNTER] += 1;
	if (start_check(input, *tokvar, x[I]) == ERROR || end_check(input, x[I]) == ERROR)
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
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	x[I] += ms_tiktok(&input[x[I]]).len;
	while (input[x[I]] && ms_isws(input[x[I]]))
		x[I]++;
	while (input[x[I]] && ((ms_tiktok(&input[x[I]]).type == CMD) || (q[0] == 1
				|| q[1] == 1)))
	{
		q[0] ^= (input[x[I]] == '\"');
		q[1] ^= (input[x[I]] == '\'');
		x[I]++;
	}
}

void	count_tokens_helper5(int *x, int *quotes, char *input)
{
	quotes[0] ^= (input[x[I]] == DQUOTE);
	quotes[1] ^= (input[x[I]] == SQUOTE);
	x[TRI] = 1;
	x[I]++;
}

void	count_tokens_helper6(int *x, char *input)
{
	while (input[x[I]] && (ms_tiktok(&input[x[I]]).type == D_AL
			|| ms_tiktok(&input[x[I]]).type == S_AL
			|| ms_tiktok(&input[x[I]]).type == S_AR
			|| ms_tiktok(&input[x[I]]).type == D_AR))
		count_tokens_helper3(x, input);
}
