/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:36:10 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 16:06:41 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ms_wlcmd(char *input)
{
	if (ms_tiktok(input).type == CMD
	|| ms_tiktok(input).type == D_AL
	|| ms_tiktok(input).type == S_AL
	|| ms_tiktok(input).type == D_AR
	|| ms_tiktok(input).type == S_AR)
		return (TRUE);
	return (ERROR);
}

int ms_wlcmdtok(char *input)
{
	if (ms_tiktok(input).type == D_AL
	|| ms_tiktok(input).type == S_AL
	|| ms_tiktok(input).type == D_AR
	|| ms_tiktok(input).type == S_AR)
		return (TRUE);
	return (ERROR);
}


int	ms_wltoken(char *input)
{
	if (ms_tiktok(input).type == P_O
	|| ms_tiktok(input).type == P_C
	|| ms_tiktok(input).type == PIPE
	|| ms_tiktok(input).type == AND
	|| ms_tiktok(input).type == OR)
		return (TRUE);
	return (ERROR);
}

int		count_tokens(char *input)
{
	int	i;
	int	counter;
	int	trigger;
	int	q[2];

	i = 0;
	counter = 0;
	trigger = 0;
	q[0] = 0;
	q[1] = 0;
	while(input[i])
	{
		trigger = 0;
		while (input[i] && ms_isws(input[i]))
			i++;
		while (input[i] && (ms_wlcmd(&input[i]) == TRUE || (q[0] || q[1])))
		{
			q[0] ^= (input[i] == '\"');
			while(input[i] && q[0])
            {
                (i)++;
				q[0] ^= (input[i] == '\"');
            }
			q[1] ^= (input[i] == '\'');
			while(input[i] && q[1])
            {
                (i)++;
				q[1] ^= (input[i] == '\'');
            }
			trigger = 1;
			i++;
		}
		while (input[i] && ms_isws(input[i]))
			i++;
		if (trigger == 1)
        {
			counter += 1;
        }
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

