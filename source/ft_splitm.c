/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:02:17 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/08 17:42:39 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	*count_quotes(char *str)
{
	int	i;
	int	*quotes;

	i = 0;
	quotes = (int *) ft_calloc(3, sizeof(int));
	while (str[i])
	{
		if (str[i] == SQUOTE)
			quotes[0]++;
		else if (str[i] == DQUOTE)
			quotes[1]++;
		i++;
	}
	return (quotes);
}

static int	count_words(char *str)
{
	int	i;
	int	trigger;
	int count;
	int	dt;

	count = 0;
	i = 0;
	dt = 0;
	while (str[i])
	{
		trigger = 0;
		while ((str[i] && !ms_isws(str[i])) || (str[i] && dt == 1))
		{
			if (str[i] == DQUOTE)
				dt ^= 1;
			trigger = 1;
			i++;
		}
		if (trigger == 1 && dt == 0)
			count++;
		while (str[i] && ms_isws(str[i]))
			i++;
	}
	return (count);
}

void	fill_split(char **split, char *str)
{
	int	i;
	int	j;
	int	k;
	int	dt;
	int	trigger;

	i = 0;
	j = 0;
	k = 0;
	dt = 0;
	while (str[i])
	{
		trigger = 0;
		k = 0;
		while ((str[i] && !ms_isws(str[i])) || (str[i] && dt == 1))
		{
			if (str[i] == DQUOTE)
				dt ^= 1;
			trigger = 1;
			k++;
			i++;
		}
		if (trigger == 1 && dt == 0)
		{
			split[j] = ft_substr(str, i - k, k);
			j++;
		}
		while (str[i] && ms_isws(str[i]))
			i++;
	}
}

char	**ft_splitm(char *str)
{
	char	**split;
	int		*quotes;
	int		wc;

	quotes = count_quotes(str);
	if (quotes[0] % 2 || quotes[1] % 2)
	{
		free(quotes);
		return (NULL);
	}
	wc = count_words(str);
	printf("STR = %s, WC = %d\n", str, wc);
	printf("SQ = %d, DQ = %d\n", quotes[0], quotes[1]);
	split = (char **) ft_calloc(count_words(str) + 1, sizeof(char *));
	fill_split(split, str);
	// for(int k = 0; split[k]; k++)
	// 	printf("STR[%d] %s\n", k, split[k]);
	return (split);
}

