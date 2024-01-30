/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 16:23:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/30 15:00:57 by bvan-pae         ###   ########.fr       */
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
		if (x[TRIGGER])
			x[COUNT]++;
		while (str[x[IX]] && ms_isws(str[x[IX]]))
			x[IX]++;
	}
	return (x[COUNT]);
}

void	fill_split(char **split, char *str)
{
	int	x[6];

	if (ms_setint(&x[I], 0), ms_setint(&x[J], 0), ms_setint(&x[3], 0),
		ms_setint(&x[4], 0), str)
		(void)str;
	while (ms_setint(&x[K], 0), str[x[I]])
	{
		x[5] = 0;
		while ((str[x[I]] && !ms_isws(str[x[I]])) || (str[x[I]] && (x[3] || x[4])))
		{
			// ft_printf("STR[%d] = |%c|\n", x[I], str[x[I]]);
			x[3] ^= (str[x[I]] == DQUOTE);
			x[4] ^= (str[x[I]] == SQUOTE);
			x[5] = 1;
			x[K]++;
			x[I]++;
		}
		if (x[5] == 1)
		{
			split[x[J]] = ft_substr(str, x[I] - x[K], x[K]);
			x[J]++;
		}
		while (str[x[I]] && ms_isws(str[x[I]]))
			x[I]++;
	}
}

int	check_dollar(char **split, t_env *denv)
{
	char *tmp;
	
	tmp = NULL;
	if (split[0] && split[0][0] == '$')
		tmp = r_env(split[0], denv);
	if (tmp && ft_strlen(tmp) == 0)
		return (free(tmp), ERROR);
	return (TRUE);
}

void	transform_split(char **split, t_env *denv)
{
	t_starlist	*strl;
	int			x[2];
	int			flag;

	x[I] = 0;
	flag = 0;
	strl = NULL;
	// ft_printf("LOL");
	// for (int i = 0; split[i]; i++)
		// ft_printf("SPLIT [%d] = %fs\n", i, split[i]);
	if (check_dollar(split, denv) == ERROR)
	{
		flag = 1;
		// ft_printf("FDP");
		// int i = 1;
		// if (split[i])
		// {
		// 	while (split[i])
		// 	{
		// 		split[i - 1] = split[i];
		// 		i++;
		// 	}
		// 	split[i - 1] = NULL;
		// 	// for(int j = 0; split[j]; j++)
		// 	// 	ft_printf("split[%d] = %fs\n", j, split[j]);
		// 	return ;
		// }
		free(split[x[0]]);
		split[x[0]] = ft_strdup_char(-19);
		if (split[1] == NULL)
        {
			return ;
        }
	}
	int i = 1;
	if (split[i] && flag == 1)
	{
		while (split[i])
		{
			split[i - 1] = split[i];
			i++;
		}
		split[i - 1] = NULL;
	}
	// for(int i = 0; split[i]; i++)
	// 	ft_printf("split[i] = %fs\n", split[i]);
	while (ms_setint(&x[J], ZERO), split[x[I]])
	{
		split[x[I]] = tild_expand(split[x[I]], denv);
		while (split[x[I]][x[J]])
		{
			if (split[x[I]][x[J]] != '\'' && split[x[I]][x[J]] != '\"')
				ms_sab(&strl, ms_snew(r_env(ms_xt(split[x[I]], &x[J], ZERO),
							denv), 0));
			else if (split[x[I]][x[J]] == '\"')
				ms_sab(&strl, ms_snew(r_env(ms_xt(split[x[I]], &x[J], '\"'),
							denv), 0));
			else if (split[x[I]][x[J]] == '\'')
				ms_sab(&strl, ms_snew(ms_xt(split[x[I]], &x[J], '\''), 0));
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

	wc = count_words(str);
	// ft_printf("SPLIT WC = %d\n", wc);
	split = (char **)ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
	{
		return (dupdup());
	}
	// ft_printf("STR = %fs\n", str);
	fill_split(split, str);
	transform_split(split, denv);
	return (split);
}
