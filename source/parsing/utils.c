/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:51:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/08 08:57:44 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

char ***ms_copy_tok(char ***tokens, int t_size)
{
	char ***tok_copy;
	int	i;
	int j;

	tok_copy = ft_calloc(t_size + 2, sizeof(char **));
	i = 0;
	while (tokens[i])
	{
		tok_copy[i] = ft_calloc(ms_tablen(tokens[i]) + 1, sizeof(char *));
		j = 0;
		while (tokens[i][j])
		{
			tok_copy[i][j] = ft_strdup(tokens[i][j]);
			j++;
		}
		i++;
	}
	return (tok_copy);
}

int	ms_count_words(char *input)
{
	int i;
	int counter;
	int trigger;

	i = 0;
	counter = 0;
	while (input[i])
	{
		trigger = 0;
		while (input[i] && ms_isws(input[i]))
			i++;
		while (input[i] && !ms_isws(input[i]))
		{
			i++;
			trigger = 1;
		}
		if (trigger == 1)
			counter += 1;
	}
	return (counter);
}
