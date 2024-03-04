/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 11:02:15 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ms_single_quote_transform(char **split, t_env *denv, int *x, t_tok *tdata)
{
	char	*tmp;

	if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], ZERO), denv, tdata);
		ms_sab(&(tdata->strl), ms_snew(tmp, 0));
		x[3] += (x[3] != 0);
		x[2] = x[3];
		x[3] += ft_strlen(tmp) - 1;
	}
}

int	ms_double_quote_transform(char **split, t_env *denv, int *x, t_tok *tdata)
{
	char	*tmp;
	int		t;

	t = x[J] - x[5];

	if (split[x[I]][x[J]] == '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], '\"'), denv, tdata);
		ms_sab(&(tdata->strl), ms_snew(tmp, 0));
		x[2] = t;
		x[3] = t + ft_strlen(tmp) - 1;
		x[5] += 2;
		return (TRUE);
	}
	return (ZERO);
}

int	ms_no_quote_transform(char **split, int *x, t_starlist **strl)
{
	char	*tmp;
	int		t;

	t = x[J] - x[5];
	if (split[x[I]][x[J]] == '\'')
	{
		tmp = ms_xt(split[x[I]], &x[J], '\'');
		ms_sab(strl, ms_snew(tmp, 0));
		x[2] = t;
		x[3] = t + ft_strlen(tmp) - 1;
		x[5] += 2;
		return (TRUE);
	}
	return (ZERO);
}

char **ts_helper(int *x, char **split, t_tok *tdata, t_ts *ts, int index)
{
	if (tdata->type[index][x[I]] == CMD)
	{
		ts->p1 = ms_cuttab(split, 0, x[I] - 1);
		ts->p2 = ms_cuttab(split, x[I] + 1, ms_tablen(split) - 1);
		ts->xi = x[I];
		ts->index = index;
		ts->new = ms_joinparts(ts, split[x[I]], tdata);
		free_tab(split);
		split = ts->new;
		x[I] = ts->xi;
	}
	else
		x[I]++;
	return (split);
}

char	**transform_split(char **split, t_env *denv, t_tok *tdata, int index)
{
	int	x[6];
	t_ts	ts;

	x[I] = 0;
	tdata->strl = NULL;
	while (ms_setint(&x[J], ZERO), ms_setint(&tdata->w_size, ZERO),
		ms_setint(&x[2], ZERO), ms_setint(&x[3], ZERO), ms_setint(&x[5], ZERO), split[x[I]])
	{
		if (ms_delimiter_expand(split, tdata, x, index) == ERROR)
			break ;
		tdata->w_pos = NULL;
		split[x[I]] = tild_expand(split[x[I]], denv);
		ms_expandsion_manager(split, denv, tdata, x);
		free(split[x[I]]);
		split[x[I]] = w_expand(ms_starjoin(&tdata->strl), denv, tdata);
		split = ts_helper(x, split, tdata, &ts, index);
		ms_starclear(&tdata->strl);
		free(tdata->w_pos);
	}
	split = ms_check_empty(split);
	return (split);
}
