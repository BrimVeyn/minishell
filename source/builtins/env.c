/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 10:13:18 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/25 14:27:45 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void b_env(t_env *denv)
{
	int	i;

	i = 0;
	while(denv->f_env[i])
		printf("%s\n", denv->f_env[i++]);
	exit(EXIT_SUCCESS);
}
