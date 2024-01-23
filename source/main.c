/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbardavi <nbabardavid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/23 15:55:33 by nbardavi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exitno = 0;

// void free_env(t_env *env)
// {
// 	free(env->usr);
// 	free(env->path);
// 	free(env->pwd);
// }

int main(int ac, char *av[], char *env[])
{
	t_env denv;

	(void) av;
	if (!env || ac >= 2)
		perror("Env is null");
	denv.f_env = ms_dupdup(env);
	denv.pwd = get_pwd(&denv);
	denv.path = get_path(&denv);
	denv.usr = get_usr(&denv);
	denv.history = NULL;
	prompt(&denv);
	ft_printf("exitno :%d\n", exitno);
	exit(exitno);
	// free_env(&denv);
}
