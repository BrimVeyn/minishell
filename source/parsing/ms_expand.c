/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 16:07:37 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/02 16:30:53 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void ms_expand(t_tok *tdata, t_env *denv)
{
    int i;
    int j;
    
    i = 0;
    while(tdata->tokens[i])
    {
        j = 0;
        while (tdata->tokens[i][j])
        {
            if (tdata->type[i][j] == CMD)
            {
                transform_split(tdata->tokens[i], denv, tdata);
                break;
            }
            j++;
        }
        i++;
    }
}
