/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:18:21 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 11:02:45 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tild_index(char *word)
{
	int	i;

	i = 0;
	while (word[i] && word[i] != '~')
		i++;
	return (i);
}

char	**dupdup(void)
{
	char	**self;

	self = ft_calloc(2, sizeof(char *));
	self[0] = ft_calloc(2, sizeof(char));
	return (self);
}

void	check_emptyness(t_tok *tdata, char *input, t_tokh *v)
{
	while (ms_isws(input[v->i]))
		v->i++;
	if (!input[v->i])
		tdata->type[v->j - 1] = WRONG;
}
