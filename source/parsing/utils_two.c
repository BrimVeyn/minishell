/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:18:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/09 08:27:11 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tild_index(char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '~')
		i++;
	return (i);
}

char	**dupdup(void)
{
	char	**self;

	self = ft_calloc(2, sizeof(char *));
	self[0] = ft_calloc(2, sizeof(char));
	return (self);
}

int	ms_wlp(char *input)
{
	if (ms_tiktok(input).type == P_O || ms_tiktok(input).type == P_C)
		return (TRUE);
	return (ERROR);
}

char	**ms_check_empty(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		if (ft_strlen(split[i]) == 0)
			split = ms_delindex(split, i);
		else
			i++;
	}
	return (split);
}

int	ms_delimiter_expand(char **split, t_tok *tdata, int *x, int index)
{
	if (tdata->type[index][x[I]] == DELIMITER)
	{
		split[x[I]] = ms_delimiter(split[x[I]]);
		x[I]++;
		if (!split[x[I]])
			return (ERROR);
	}
	return (TRUE);
}
