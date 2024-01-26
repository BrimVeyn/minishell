/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:46:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:14:41 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	*ms_word(char *word, int *i)
{
	int	*ix;

	ix = ft_calloc(3, sizeof(int));
	ix[0] = *i;
	while (word[*i] && word[*i] != '*')
		(*i)++;
	ix[1] = *i - 1;
	return (ix);
}

int	ms_starsplit_helper(int *i, char *s, int *ss)
{
	while (s[*i] && s[*i] == '*')
	{
		ss[0] = 1;
		(*i)++;
	}
	if (!s[*i])
		return (ERROR);
	return (TRUE);
}

t_starlist	*ms_starsplit(char *s)
{
	t_starlist	*sl;
	int			i;
	int			ss[2];
	int			*x;

	i = 0;
	sl = NULL;
	while (s[i])
	{
		ss[0] = 0;
		ss[1] = 0;
		if (ms_starsplit_helper(&i, s, ss) == ERROR)
			break ;
		x = ms_word(s, &i);
		ss[1] = (s[i] && s[i] == '*');
		if (ss[0] == 1 && ss[1] == 1)
			ms_sab(&sl, ms_snew(ft_substr(s, x[0], (x[1] - x[0]) + 1), MID));
		else if (ss[0] == 0 && ss[1] == 1)
			ms_sab(&sl, ms_snew(ft_substr(s, x[0], (x[1] - x[0]) + 1), START));
		else if (ss[0] == 1 && ss[1] == 0)
			ms_sab(&sl, ms_snew(ft_substr(s, x[0], (x[1] - x[0]) + 1), END));
		free(x);
	}
	return (sl);
}
