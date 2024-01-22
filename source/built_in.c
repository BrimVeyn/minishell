/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 12:53:17 by nbardavi          #+#    #+#             */
/*   Updated: 2024/01/19 13:00:33 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../include/minishell.h"

void b_pwd(char *pwd)
{
	printf("%s\n", pwd);
}

void b_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
		printf("%s\n", env[i++]);
}

void b_exit(t_pipe *d_pipe)
{
	d_pipe->t_exit = 1;
}
