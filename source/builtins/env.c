/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/26 13:20:17 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

extern int exitno;

void b_env(t_env *denv)
{
	int	i;

	i = 0;
	while(denv->f_env[i])
		printf("%s\n", denv->f_env[i++]);
	exitno = 0;
}
