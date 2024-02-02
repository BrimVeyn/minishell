/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 14:40:00 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 09:44:27 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int	g_exitno;

int	check_dollar(char **split, t_env *denv)
{
	char	*tmp;

	tmp = NULL;
	if (split[0] && split[0][0] == '$')
		tmp = r_env(split[0], denv);
	if (tmp && ft_strlen(tmp) == 0)
		return (free(tmp), ERROR);
	return (TRUE);
}

void	move_split_index(char **split, int *flag)
{
	int	i;

	i = 1;
	if (split[i] && *flag == 1)
	{
		while (split[i])
		{
			split[i - 1] = split[i];
			i++;
		}
		split[i - 1] = NULL;
	}
}

void	empty_var_setter(t_env *denv, char **split, int *x)
{
	int	flag;

	flag = 0;
	if (check_dollar(split, denv) == ERROR)
	{
		flag = 1;
		free(split[x[I]]);
		split[x[I]] = ft_strdup_char(-19);
		move_split_index(split, &flag);
		if (split[1] == NULL)
			return ;
	}
}

void	transform_split(char **split, t_env *denv)
{
	t_starlist	*strl;
	int			x[2];

	x[I] = 0;
	strl = NULL;
	empty_var_setter(denv, split, x);
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

	split = (char **)ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
		return (dupdup());
	fill_split(split, str);
	transform_split(split, denv);
	return (split);
}
