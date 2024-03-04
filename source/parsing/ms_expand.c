/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/01 13:30:52 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_expand(t_tok *tdata, t_env *denv, int index)
{
	int	j;

	j = 0;
	while (tdata->tokens[index][j])
	{
		if (ms_typecmdtok(tdata->type[index][j]) == TRUE
			|| tdata->type[index][j] == CMD)
		{
			tdata->tokens[index] = transform_split(tdata->tokens[index], denv,
					tdata, index);
			if (!ft_strcmp(tdata->tokens[index][0], "WRONG"))
				tdata->type[index][0] = WRONG;
			break ;
		}
		j++;
	}
}
