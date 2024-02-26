/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 10:00:28 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



static void	ms_single_quote_transform(char **split, t_env *denv, int *x,
		t_starlist **strl)
{
	char	*tmp;

	if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], ZERO), denv);
		ms_sab(strl, ms_snew(tmp, 0));
		x[3] += (x[3] != 0);
		x[2] = x[3];
		x[3] += ft_strlen(tmp) - 1;
	}
}

static int	ms_double_quote_transform(char **split, t_env *denv, int *x,
		t_starlist **strl)
{
	char	*tmp;

	if (split[x[I]][x[J]] == '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], '\"'), denv);
		ms_sab(strl, ms_snew(tmp, 0));
		x[3] += (x[3] != 0);
		x[2] = x[3];
		x[3] += ft_strlen(tmp) - 1;
		return (TRUE);
	}
	return (ZERO);
}

static int	ms_no_quote_transform(char **split, int *x, t_starlist **strl)
{
	char	*tmp;

	if (split[x[I]][x[J]] == '\'')
	{
		tmp = ms_xt(split[x[I]], &x[J], '\'');
		ms_sab(strl, ms_snew(tmp, 0));
		x[3] += (x[3] != 0);
		x[2] = x[3];
		x[3] += ft_strlen(tmp) - 1;
		return (TRUE);
	}
	return (ZERO);
}

void	ms_expandsion_manager(char **split, t_env *denv, t_tok *tdata, int *x)
{
	while (split[x[I]][x[J]])
	{
		ms_single_quote_transform(split, denv, x, &tdata->strl);
		if (ms_double_quote_transform(split, denv, x, &tdata->strl))
			tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, x[2], x[3]);
		if (ms_no_quote_transform(split, x, &tdata->strl))
			tdata->w_pos = ms_intab(tdata->w_pos, &tdata->w_size, x[2], x[3]);
	}
}

char	**transform_split(char **split, t_env *denv, t_tok *tdata, int index)
{
	int	x[5];

	x[I] = 0;
	tdata->strl = NULL;
	while (ms_setint(&x[J], ZERO), ms_setint(&tdata->w_size, ZERO),
		ms_setint(&x[2], ZERO), ms_setint(&x[3], ZERO), split[x[I]])
	{
		if (ms_delimiter_expand(split, tdata, x, index) == ERROR)
			break ;
		tdata->w_pos = NULL;
		split[x[I]] = tild_expand(split[x[I]], denv);
		ms_expandsion_manager(split, denv, tdata, x);
		free(split[x[I]]);
		split[x[I]] = w_expand(ms_starjoin(&tdata->strl), denv, tdata);
		ms_starclear(&tdata->strl);
		free(tdata->w_pos);
		x[I]++;
	}
	split = ms_check_empty(split);
	return (split);
}
