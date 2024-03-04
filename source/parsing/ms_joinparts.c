/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_joinparts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 10:51:12 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 10:52:07 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	jp_helper(t_jp *jp, t_ts *ts, t_tok *tdata, char *words)
{
	if (!tdata->w_pos)
	{
		jp->mid = ft_split(words, ' ');
		if (!jp->mid[0])
		{
			free_tab(jp->mid);
			jp->mid = ms_strtotab("");
		}
	}
	else
		jp->mid = ms_strtotab(words);
	jp->new = ft_calloc(ms_tablen(ts->p1) + ms_tablen(jp->mid)
			+ ms_tablen(ts->p2) + 2, sizeof(char *));
	jp->newtype = ft_calloc(ms_tablen(ts->p1) + ms_tablen(jp->mid)
			+ ms_tablen(ts->p2) + 2, sizeof(int));
	jp->j = 0;
	jp->i = 0;
	jp->k = 0;
}

void	jp_cpp1(t_jp *jp, t_ts *ts, t_tok *tdata)
{
	while (ts->p1 && ts->p1[jp->i])
	{
		jp->new[jp->j] = ft_strdup(ts->p1[jp->i]);
		jp->newtype[jp->k] = tdata->type[ts->index][jp->k];
		jp->k++;
		jp->j++;
		jp->i++;
	}
	jp->i = 0;
}

void	jp_cpmid(t_jp *jp, t_ts *ts)
{
	while (jp->mid && jp->mid[jp->i])
	{
		jp->new[jp->j] = ft_strdup(jp->mid[jp->i]);
		jp->newtype[jp->k] = CMD;
		jp->k++;
		jp->j++;
		jp->i++;
	}
	jp->i = 0;
	jp->cp = ts->xi + 1;
}

void	jp_cpp2(t_jp *jp, t_ts *ts, t_tok *tdata)
{
	while (ts->p2 && ts->p2[jp->i])
	{
		jp->new[jp->j] = ft_strdup(ts->p2[jp->i]);
		jp->newtype[jp->k] = tdata->type[ts->index][jp->cp];
		jp->k++;
		jp->cp++;
		jp->j++;
		jp->i++;
	}
}

char	**ms_joinparts(t_ts *ts, char *words, t_tok *tdata)
{
	t_jp	jp;

	jp_helper(&jp, ts, tdata, words);
	jp_cpp1(&jp, ts, tdata);
	jp_cpmid(&jp, ts);
	jp_cpp2(&jp, ts, tdata);
	ts->xi += ms_tablen(jp.mid);
	free(tdata->type[ts->index]);
	tdata->type[ts->index] = jp.newtype;
	return (free_tab(ts->p1), free_tab(ts->p2), free_tab(jp.mid), jp.new);
}
