/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 14:43:07 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int g_exitno;

void b_env(t_env *denv)
{
	int	i;

	i = 0;
	while(denv->f_env[i])
		printf("%s\n", denv->f_env[i++]);
	g_exitno = 0;
}
