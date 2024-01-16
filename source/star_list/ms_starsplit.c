/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_starsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:46:13 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/16 15:10:45 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int *ms_word(char *word, int *i)
{
	int	*ix;

	ix = ft_calloc(3, sizeof(int));
	ix[0] = *i;
	while (word[*i] && word[*i] != '*')
		(*i)++;
	ix[1] = *i - 1;
	return (ix);
}

t_starlist *ms_starsplit(char *string)
{
	t_starlist *slist;
	int	i;
	int ss[2];
	int	*ix;

	i = 0;
	slist = NULL;
	while (string[i])
	{
		ss[0] = 0;
		ss[1] = 0;
		while (string[i] && string[i] == '*')
		{
			ss[0] = 1;
			i++;
		}
		if (!string[i])
			break;
		ix = ms_word(string, &i);
		if (string[i] && string[i] == '*')
			ss[1] = 1;
		if (ss[0] == 1 && ss[1] == 1)
			ms_starlab(&slist, ms_starlnew(ft_substr(string, ix[0], (ix[1] - ix[0]) + 1), MID));
		else if (ss[0] == 0 && ss[1] == 1)
			ms_starlab(&slist, ms_starlnew(ft_substr(string, ix[0], (ix[1] - ix[0]) + 1), START));
		else if (ss[0] == 1 && ss[1] == 0)
			ms_starlab(&slist, ms_starlnew(ft_substr(string, ix[0], (ix[1] - ix[0]) + 1), END));
		free(ix);
	}
	return (slist);
}
