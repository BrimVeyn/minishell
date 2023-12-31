/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:02:17 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/09 16:28:11 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>

static	int	*count_quotes(char *str)
{
	int	i;
	int	*quotes;

	i = 0;
	quotes = (int *) ft_calloc(3, sizeof(int));
	if (!quotes)
		return (NULL);
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
	int	st;
	int	trigger;

	i = 0;
	j = 0;
	k = 0;
	dt = 0;
	st = 0;
	while (str[i])
	{
		trigger = 0;
		k = 0;
		while ((str[i] && !ms_isws(str[i])) || (str[i] && (dt == 1 || st == 1)))
		{
			if (str[i] == DQUOTE)
				dt ^= 1;
			if (str[i] == SQUOTE)
				st ^= 1;
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

char *t_squote(char *split, int *j)
{
	int	i;
	int start;
	int end;
	char *p1;
	char *new;
	char *p2;

	i = 0;
	while(split[i] && split[i] != SQUOTE)
		i++;
	start = i + 1;
	i++;
	while (split[i] && split[i] != SQUOTE)
		i++;
	end = i;
	p1 = ft_substr(split, 0, start - 1);
	new = ft_substr(split, start, end - start);
	p2 = ft_substr(split, end + 1, (ft_strlen(split) - end));
	printf("p1 : %s, new : %s, p2 : %s\n", p1, new, p2);
	char *final = ft_sprintf("%s%s%s", p1, new, p2);
	printf("final : %s\n", final);
	*j = end - 1;
	return (final);
}

char *r_env(char *split)
{
	int	i;
	int start;
	int end;
	char *p1;
	char *var;
	char *p2;
	char *new;

	i = 0;
	while (split[i])
	{
		if (split[i] == '$')
		{
			start = i + 1;
			while (split[i] && split[i] != ' ' && split[i] != '\'')
				i++;
			end = i;
			p1 = ft_substr(split, 0, start - 1);
			var = getenv(ft_substr(split, start, end - start));
			p2 = ft_substr(split, end, (ft_strlen(split) - end));
			if (!var)
				split = ft_sprintf("%s%s%s", p1, var, p2);
			else
				split = ft_sprintf("%s%fs%s", p1, var, p2);
			i = ft_strlen(split) - end;
			// new = ft_sprintf("%s%s%s", p1, var, p2);
			// printf("P1 = %s\nP2 = %s\nVAR = %s\n", p1, p2, var);
		}
		i++;
	}
	return (split);
}

char *t_dquote(char *split, int *j)
{
	int	i;
	int	start;
	int	end;
	char *p1;
	char *new;
	char *p2;

	i = 0;
	while (split[i] && split[i] != DQUOTE)
		i++;
	start = i + 1;
	i++;
	while (split[i] && split[i] != DQUOTE)
		i++;
	end = i;
	p1 = ft_substr(split, 0, start - 1);
	new = r_env(ft_substr(split, start, end - start));
	p2 = ft_substr(split, end + 1, (ft_strlen(split) - end));
	*j = ft_strlen(p1) + ft_strlen(new);
	// printf("POINTER = %d\n", *j);
	return(ft_sprintf("%s%s%s", p1, new, p2));
}

void	transform_split(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		while(split[i][j])
		{
			if (split[i][j] == SQUOTE)
			{
				split[i] = t_squote(split[i], &j);
				// printf("SRESTE = %s\n",split[i]);
			}
			if (split[i][j] == DQUOTE)
			{
				split[i] = t_dquote(split[i], &j);
				// printf("DRESTE = %s\n",split[i]);
			}
			j++;
		}
		i++;
	}
}

char	**ft_splitm(char *str)
{
	char	**split;
	int		*quotes;
	int		wc;

	quotes = count_quotes(str);
	if (quotes == NULL || quotes[0] % 2 || quotes[1] % 2)
	{
		free(quotes);
		return (NULL);
	}
	wc = count_words(str);
	printf("STR = %s, WC = %d\n", str, wc);
	printf("SQ = %d, DQ = %d\n", quotes[0], quotes[1]);
	split = (char **) ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
	{
		free(quotes);
		return (NULL);
	}
	fill_split(split, str);
	transform_split(split);
	free(quotes);
	// for(int k = 0; split[k]; k++)
	// 	printf("STR[%d] %s\n", k, split[k]);
	return (split);
}

