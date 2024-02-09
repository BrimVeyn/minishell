/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:36:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 10:23:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	skip_word(char *input, int *trigger, int *counter, int *i)
{
	int	q[2];

	q[0] = 0;
	q[1] = 0;
	while (input[*i] && (ms_wlcmd(&input[*i]) == TRUE || (q[0] || q[1])))
	{
		q[0] ^= (input[*i] == '\"');
		while (input[*i] && q[0])
		{
			(*i)++;
			q[0] ^= (input[*i] == '\"');
		}
		q[1] ^= (input[*i] == '\'');
		while (input[*i] && q[1])
		{
			(*i)++;
			q[1] ^= (input[*i] == '\'');
		}
		*trigger = 1;
		(*i)++;
	}
	while (input[*i] && ms_isws(input[*i]))
		(*i)++;
	if (*trigger == 1)
		*counter += 1;
}

int	count_tokens(char *input)
{
	int	i;
	int	counter;
	int	trigger;

	i = 0;
	counter = 0;
	trigger = 0;
	while (input[i])
	{
		trigger = 0;
		while (input[i] && ms_isws(input[i]))
			i++;
		skip_word(input, &trigger, &counter, &i);
		if (input[i] && ms_wltoken(&input[i]) == TRUE)
		{
			i += ms_tiktok(&input[i]).len;
			counter += 1;
		}
		while (input[i] && ms_isws(input[i]))
			i++;
	}
	return (counter);
}
