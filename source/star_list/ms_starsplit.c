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

int ms_isinw_pos(int i, t_tok *tdata)
{
    int j;

    j = 0;
    while (j < tdata->w_size)
    {
        if (i >= tdata->w_pos[j] && i <= tdata->w_pos[j + 1])
            return (TRUE);
        j += 2;
    }
    return (ERROR);
}

int	*ms_word(char *word, int *i, t_tok *tdata)
{
	int	*ix;

	ix = ft_calloc(3, sizeof(int));
	ix[0] = *i;
	while (word[*i] && ((word[*i] != '*') || (word[*i] == '*' && ms_isinw_pos(*i, tdata) == TRUE)))
		(*i)++;
	ix[1] = *i - 1;
    // ft_printf("ix[0] = %d, ix[1] = %d\n", ix[0], ix[1]);
	return (ix);
}

int	ms_starsplit_helper(int *i, char *s, int *ss, t_tok *tdata)
{
	while (s[*i] && s[*i] == '*' && ms_isinw_pos(*i, tdata) == ERROR)
	{
		ss[0] = 1;
		(*i)++;
	}
	if (!s[*i])
		return (ERROR);
	return (TRUE);
}

t_starlist	*ms_starsplit(char *s, t_tok *tdata)
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
		if (ms_starsplit_helper(&i, s, ss, tdata) == ERROR)
			break ;
		x = ms_word(s, &i, tdata);
		ss[1] = (s[i] && s[i] == '*' && ms_isinw_pos(i, tdata) == ERROR);
        // ft_printf("ss[0] = %d, ss[1] = %d\n", ss[0], ss[1]);
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
