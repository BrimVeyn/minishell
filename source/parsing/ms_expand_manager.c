/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand_manager.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/27 16:56:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"



static void	ms_single_quote_transform(char **split, t_env *denv, int *x,
		t_starlist **strl, t_tok *tdata)
{
	char	*tmp;

	if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], ZERO), denv, tdata);
		ms_sab(strl, ms_snew(tmp, 0));
		x[3] += (x[3] != 0);
		x[2] = x[3];
		x[3] += ft_strlen(tmp) - 1;
	}
}

static int	ms_double_quote_transform(char **split, t_env *denv, int *x,
		t_starlist **strl, t_tok *tdata)
{
	char	*tmp;

	if (split[x[I]][x[J]] == '\"')
	{
		tmp = r_env(ms_xt(split[x[I]], &x[J], '\"'), denv, tdata);
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
		ms_single_quote_transform(split, denv, x, &tdata->strl, tdata);
		if (ms_double_quote_transform(split, denv, x, &tdata->strl, tdata))
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

typedef struct s_ts
{
	char **p1;
	char **p2;
	int	 xi;
	int  index;

}	t_ts;

char **ms_joinparts(t_ts *ts, char *words, t_tok *tdata)
{
	char **mid;
	char **new;
	int *newtype;
	int i;
	int j;

	if (!tdata->w_pos)
		mid = ft_split(words, ' ');
	else
		mid = ft_split(words, '\n');
	new = ft_calloc(ms_tablen(ts->p1) + ms_tablen(mid) + ms_tablen(ts->p2) + 2, sizeof(char *));
	newtype = ft_calloc(ms_tablen(ts->p1) + ms_tablen(mid) + ms_tablen(ts->p2) + 2, sizeof(int));
	j = 0;
	i = 0;
	int k = 0;
	while (ts->p1 && ts->p1[i])
    {
		new[j] = ft_strdup(ts->p1[i]);
		newtype[k] = tdata->type[ts->index][k];
		printf("SET TYPE %d to %d\n", k, tdata->type[ts->index][k]);
		k++;
		j++;
		i++;
    }
	i = 0;
	while(mid && mid[i])
	{
		new[j] = ft_strdup(mid[i]);
		newtype[k] = CMD;
		printf("SET TYPE %d to %d\n", k, CMD);
		k++;
		j++;
		i++;
	}
	i = 0;
	int cp = ts->xi + 1;
	printf("xi = %d\n", cp);
	printf("type xi = %d\n", tdata->type[ts->index][cp]);
	while (ts->p2 && ts->p2[i])
	{
		new[j] = ft_strdup(ts->p2[i]);
		newtype[k] = tdata->type[ts->index][cp];
		printf("SET TYPE %d to %d\n", k, tdata->type[ts->index][cp]);
		k++;
		cp++;
		j++;
		i++;
	}
	ts->xi += ms_tablen(mid);
	free(tdata->type[ts->index]);
	tdata->type[ts->index] = newtype;
	return (free_tab(ts->p1), free_tab(ts->p2), free_tab(mid), new);
}

char	**transform_split(char **split, t_env *denv, t_tok *tdata, int index)
{
	int	x[5];
	t_ts	ts;

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
		if (tdata->type[index][x[I]] == CMD)
		{
			for(int k = 0; tdata->tokens[index][k]; k++)
				printf("TYPE[%d] = %d\n", k, tdata->type[index][k]);
			ts.p1 = ms_cuttab(split, 0, x[I] - 1);
			ts.p2 = ms_cuttab(split, x[I] + 1, ms_tablen(split) - 1);
			ts.xi = x[I];
			ts.index = index;
			char **new = ms_joinparts(&ts, split[x[I]], tdata);
			for(int k = 0; tdata->w_pos && tdata->w_pos[k]; k++)
				printf("tdata->w_pos[%d] = %d\n", k, tdata->w_pos[k]);
			free_tab(split);
			split = new;
			x[I] = ts.xi;
        }
		else
		{
			(void) ts;
			x[I]++;
		}
		ms_starclear(&tdata->strl);
		free(tdata->w_pos);
	}
	split = ms_check_empty(split);
	return (split);
}
