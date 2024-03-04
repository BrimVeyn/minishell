/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:53:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 11:00:46 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_expandsion_manager(char **split, t_env *denv, t_tok *tdata, int *x)
{
	while (split[x[I]][x[J]])
	{
		ms_single_quote_transform(split, denv, x, tdata);
		if (ms_double_quote_transform(split, denv, x, tdata))
			tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, x[2], x[3]);
		if (ms_no_quote_transform(split, x, &tdata->strl))
			tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, x[2], x[3]);
	}
}

char **ms_cuttab(char **tab, int start, int end)
{
	char **new;
	int i;

	i = 0;
	if (end < start || !tab[start] || !tab[end])
		return (NULL);
	new = ft_calloc(end - start + 2, sizeof(char *));
	while(start <= end)
	{
		new[i] = ft_strdup(tab[start]);
		i++;
		start++;
	}
	return (new);
}

char **ms_strtotab(char *str)
{
	char **mid;

	mid = ft_calloc(2, sizeof(char *));
	mid[0] = ft_strdup(str);
	return (mid);
}
