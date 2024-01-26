/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:23:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:30:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

static int	count_words(char *str)
{
	int	x[5];

	if (ms_setint(&x[COUNT], 0), ms_setint(&x[IX], 0), ms_setint(&x[DQ], 0),
		ms_setint(&x[SQ], 0), str)
		(void)str;
	while (str[x[IX]])
	{
		x[TRIGGER] = 0;
		while ((str[x[IX]] && !ms_isws(str[x[IX]])) || (str[x[IX]] && (x[DQ] || x[SQ])))
		{
			x[DQ] ^= (str[x[IX]] == DQUOTE);
			x[SQ] ^= (str[x[IX]] == SQUOTE);
			x[TRIGGER] = 1;
			x[IX]++;
		}
		if (x[TRIGGER] && x[DQ] == 0 && x[SQ] == 0)
			x[COUNT]++;
		while (str[x[IX]] && ms_isws(str[x[IX]]))
			x[IX]++;
	}
	return (x[COUNT]);
}

void	fill_split(char **split, char *str)
{
	int	x[5];
	int	trigger;

	if (ms_setint(&x[I], 0), ms_setint(&x[J], 0), ms_setint(&x[3], 0),
		ms_setint(&x[4], 0), str)
		(void)str;
	while (ms_setint(&x[K], 0), str[x[I]])
	{
		trigger = 0;
		while ((str[x[I]] && !ms_isws(str[x[I]])) || (str[x[I]] && (x[3] || x[4])))
		{
			x[3] ^= (str[x[I]] == DQUOTE);
			x[4] ^= (str[x[I]] == SQUOTE);
			trigger = 1;
			x[K]++;
			x[I]++;
		}
		if (trigger == 1 && !(x[3]) && !(x[4]))
		{
			split[x[J]] = ft_substr(str, x[I] - x[K], x[K]);
			x[J]++;
		}
		while (str[x[I]] && ms_isws(str[x[I]]))
			x[I]++;
	}
}

void	transform_split(char **split, t_env *denv)
{
	t_starlist	*strl;
	int			x[2];

	x[I] = 0;
	strl = NULL;
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
		// ft_printf("--------------------------------\n");
		split[x[I]] = tild_expand(split[x[I]], denv);
		while (split[x[I]][x[J]])
		{
			if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
				ms_sab(&strl, ms_snew(r_env(ms_extract(split[x[I]], &x[J], ZERO), denv), 0));
			else if (split[x[I]][x[J]] == '\"')
				ms_sab(&strl, ms_snew(r_env(ms_extract(split[x[I]], &x[J], '\"'), denv), 0));
			else if (split[x[I]][x[J]] == '\'')
				ms_sab(&strl, ms_snew(ms_extract(split[x[I]], &x[J], '\''), 0));
		}
		free(split[x[I]]);
		split[x[I]] = w_expand(ms_starjoin(&strl), denv);
		ms_starclear(&strl);
		x[I]++;
	}
}

char	**ft_splitm(char *str, t_env *denv)
{
	char	**split;
	int		wc;

	// printf("EXITNO  %d\n", tdata->g_exitno);
	// ft_printf("%d %d", quotes[0], quotes[1]);
	wc = count_words(str);
	// printf("STR = %s, WC = %d\n", str, wc);
	// printf("SQ = %d, DQ = %d\n", quotes[0], quotes[1]);
	// printf("WC = %d\n", wc);
	split = (char **)ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
	{
		return (dupdup());
	}
	fill_split(split, str);
	// for(int i = 0; split[i]; i++)
	// 	printf("SPLIT[%d] = %s\n", i, split[i]);
	transform_split(split, denv);
	// for(int k = 0; split[k]; k++)
	// 	printf("STR[%d] %s\n", k, split[k]);
	return (split);
}
