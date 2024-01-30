/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_splitm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 17:22:55 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 17:23:42 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_words(char *str)
{
	int	x[5];

	if (ms_setint(&x[COUNT], 0), ms_setint(&x[IX], 0), ms_setint(&x[DQ], 0),
		ms_setint(&x[SQ], 0), str)
		(void)str;
	while (str[x[IX]])
	{
		x[TRIGGER] = 0;
		while ((str[x[IX]] && !ms_isws(str[x[IX]])) || (str[x[IX]] && (x[DQ]
					|| x[SQ])))
		{
			x[DQ] ^= (str[x[IX]] == DQUOTE);
			x[SQ] ^= (str[x[IX]] == SQUOTE);
			x[TRIGGER] = 1;
			x[IX]++;
		}
		if (x[TRIGGER])
			x[COUNT]++;
		while (str[x[IX]] && ms_isws(str[x[IX]]))
			x[IX]++;
	}
	return (x[COUNT]);
}

void	fill_split(char **split, char *str)
{
	int	x[6];

	if (ms_setint(&x[I], 0), ms_setint(&x[J], 0), ms_setint(&x[3], 0),
		ms_setint(&x[4], 0), str)
		(void)str;
	while (ms_setint(&x[K], 0), str[x[I]])
	{
		x[5] = 0;
		while ((str[x[I]] && !ms_isws(str[x[I]])) || (str[x[I]] && (x[3]
					|| x[4])))
		{
			x[3] ^= (str[x[I]] == DQUOTE);
			x[4] ^= (str[x[I]] == SQUOTE);
			x[5] = 1;
			x[K]++;
			x[I]++;
		}
		if (x[5] == 1)
		{
			split[x[J]] = ft_substr(str, x[I] - x[K], x[K]);
			x[J]++;
		}
		while (str[x[I]] && ms_isws(str[x[I]]))
			x[I]++;
	}
}
