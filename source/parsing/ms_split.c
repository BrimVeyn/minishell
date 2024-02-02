/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 16:30:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int ms_count_word(char **input)
{
	int counter;
	int q[2];
	int trigger;

	counter = 0;
	trigger = 0;
	q[0] = 0;
	q[1] = 0;
	while ((*input) && ms_wlcmd((*input)))
	{
		while (ms_isws((**input)))
			(*input)++;
		q[0] ^= ((**input) == '\"');
		while((*input) && q[0])
		{
			q[0] ^= ((**input) == '\"');
			(*input)++;
		}
		q[1] ^= ((**input) == '\'');
		while((*input) && q[1])
		{
			q[1] ^= ((**input) == '\'');
			(*input)++;
		}
		trigger = 1;
		(*input)++;
		while (ms_isws((**input)))
			(*input)++;
	}
	return (counter);
}


char ***ms_split(t_tok *tdata, t_env *denv, char *input)
{
	char ***split;
	int i;
	int wc;

	(void) denv;
	i = 0;
	wc = 0;
	split = (char ***) ft_calloc(tdata->t_size + 1, sizeof(char **));
	while (i < tdata->t_size)
	{
		ft_printf("input = %fs\n", input);
		wc = ms_count_word(&input);
		ft_printf("input = %fs\n", input);
		split[i] = (char **) ft_calloc(wc + 1, sizeof(char *));
		i++;
	}

	return (split);
}
