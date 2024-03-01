/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:51:05 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/01 16:01:22 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


char	***ms_copy_tok(char ***tokens, int t_size)
{
	char	***tok_copy;
	int		i;
	int		j;

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
	int	i;
	int	counter;
	int	trigger;

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

char	**ms_delindex(char **split, int i)
{
	char	**new;
	int		j;
	int		k;

	j = 0;
	k = 0;
	new = ft_calloc(ft_strlenlen(split) + 1, sizeof(char *));
	while (split[j] && j != i)
	{
		new[k++] = ft_strdup(split[j]);
		j++;
	}
	j++;
	while (split[j])
	{
		new[k++] = ft_strdup(split[j]);
		j++;
	}
	if (!new[0])
		new[0] = ft_strdup("WRONG");
	free_tab(split);
	return (new);
}

char	*ms_delimiter(char *delimiter)
{
	char	*new;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(delimiter) - 1;
	if (((delimiter[start] == '\"' && delimiter[end] == '\"')
			|| (delimiter[start] == '\'' && delimiter[end] == '\''))
		&& end > start)
	{
		start += 1;
		end -= 1;
	}
	new = ft_substr(delimiter, start, end - start + 1);
	return (free(delimiter), new);
}

int	*ms_intab(int *w_pos, int *w_size, int p_a, int p_b)
{
	int	*new;
	int	new_size;
	int	i;

	if (!w_size)
		new_size = 3;
	else
		new_size = *w_size + 2;
	new = ft_calloc(new_size, sizeof(int));
	i = 0;
	while (i < *w_size)
	{
		new[i] = w_pos[i];
		i++;
	}
	new[i++] = p_a;
	new[i] = p_b;
	*w_size += 2;
	return (free(w_pos), new);
}
