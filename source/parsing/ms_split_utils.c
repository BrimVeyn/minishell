/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 08:30:11 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 08:30:23 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_fill_cmd(char **split, char *input, int *j, int *type)
{
	int	q[2];
	int	x[4];

	x[1] = 0;
	q[0] = 0;
	q[1] = 0;
	x[0] = 0;
	while (input[*j] && ms_wltoken(&input[*j]) == ERROR)
	{
		x[1] = 0;
		while (input[(*j)] && ms_isws(input[*j]))
			(*j)++;
		x[2] = *j;
		ms_fill_word(input, j, q, &x[1]);
		x[3] = *j;
		ms_type_set(input, x, type, split);
		*j = x[3];
	}
}

void	ms_fill_token(char **split, char *input, int *j, int *type)
{
	split[0] = ft_strdup(ms_tiktok(&input[*j]).str);
	type[0] = ms_tiktok(&input[*j]).type;
}
