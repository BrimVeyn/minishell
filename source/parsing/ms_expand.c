/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/27 16:06:39 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ms_expand(t_tok *tdata, t_env *denv)
{
	int	i;
	int	j;

	i = 0;
	while (tdata->tokens[i])
	{
		j = 0;
		while (tdata->tokens[i][j])
		{
			if (ms_typecmdtok(tdata->type[i][j]) == TRUE
				|| tdata->type[i][j] == CMD)
			{
				tdata->tokens[i] = transform_split(tdata->tokens[i], denv,
						tdata, i);
				if (!ft_strcmp(tdata->tokens[i][0], "WRONG"))
					tdata->type[i][0] = WRONG;
				break ;
			}
			j++;
		}
		i++;
	}
}
