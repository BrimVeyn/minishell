/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 15:16:24 by bvan-pae          #+#    #+#             */
/*   Updated: 2023/12/26 16:25:06 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void free_env(t_env *env)
{
	free(env->usr);
	free(env->path);
	free(env->pwd);
}

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
	// printf("%s\n", denv.pwd);
	// printf("%s\n", denv.path);
	// printf("%s\n", denv.usr);
	char *c_line = "\"";
	// for (int i = 0; c_line[i]; i++)
	// 	printf("%d\n", c_line[i]);
	prompt(&denv);
	free_env(&denv);
}
