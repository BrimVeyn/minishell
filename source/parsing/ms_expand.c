/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/03/04 15:48:48 by bvan-pae         ###   ########.fr       */
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
				tdata->type[index][0] = IGNORE;
			break ;
		}
		j++;
	}
}

void	ms_parse(t_tok *tdata, t_env *denv, int index)
{
	ms_expand(tdata, denv, index);
	ms_add_path(tdata, denv, index);
	if (ms_ambiguous_error(tdata, index) == ERROR)
	{
		tdata->exitno = 1 << 8;
		tdata->t_size = ERROR;
		tdata->type[index][0] = IGNORE;
	}
}
