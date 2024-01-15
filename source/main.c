/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/01/15 17:21:08 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int exitno = 0;

void free_env(t_env *env)
{
	free(env->usr);
	free(env->path);
	free(env->pwd);
}

int main(int ac, char *av[], char *env[])
{
	t_env *denv = ft_calloc(2, sizeof(t_dlist));

	(void) av;
	if (!env || ac >= 2)
		perror("Env is null");
	denv->f_env = ms_dupdup(env);
	denv->pwd = get_pwd(denv);
	denv->path = get_path(denv);
	denv->usr = get_usr(denv);
	denv->flist = get_flist(denv);
	// ms_dprint(&denv.flist);
	prompt(denv);
	free_env(denv);
}
