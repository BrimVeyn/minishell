/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/02/26 11:21:56 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	b_env(t_env *denv, t_tok *tdata)
{
	int	i;

	i = 0;
	while (denv->f_env[i])
		printf("%s\n", denv->f_env[i++]);
	tdata->exitno = 0;
}
